#include "modulewidget.h"
#include "ui_modulewidget.h"
#include <QtWebKitWidgets/QWebView>
#include <QtNetwork>

ModuleWidget::ModuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleWidget)
{
    ui->setupUi(this);
    //set Layout to deal with Responsive Layout
    QGridLayout *moduleLayout = new QGridLayout(this);
    moduleLayout->addWidget(ui->gridLayoutWidget);
    //set property of QWebPage
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    prepareNetManager();
    connect(netManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply_show_module(QNetworkReply*)));
}

ModuleWidget::~ModuleWidget()
{
    delete ui;
}

void ModuleWidget::callServer(QString strUrl)
{
    QNetworkRequest req;
    req.setUrl(QUrl(strUrl));
    netManager->get(req);
}

void ModuleWidget::fetch_selected_data_md(QList<QString> list)
{
    orgaHandler = new OrganismHandler;
    QString preUrl = QString("http://localhost/mCell/api/pathway/ko.php?id=");
    QString str,ids;
    foreach (str, list) {
        ids.append(orgaHandler->organismMap[str].trimmed());
    }
    QString url = preUrl + ids;
    callServer(url);
}

void ModuleWidget::reply_show_module(QNetworkReply *reply)
{
    int status;
    QList<QString> koList;
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    jDoc = QJsonDocument::fromJson(all.toUtf8(), &jError);
    if(jError.error == QJsonParseError::NoError) {
        if(jDoc.isObject()) {
            QVariantMap objMap = jDoc.toVariant().toMap();
            status = objMap["status"].toInt();
            if(!status) {
                foreach (QVariant ko, objMap["ko_arr"].toList()) {
                    koList.append(ko.toString());
                }
            }
        }
    }
    generateModule(koList);
}

void ModuleWidget::on_webView_linkClicked(const QUrl url)
{
    ui->webView->load(url);
}

void ModuleWidget::prepareNetManager()
{
    netManager = new QNetworkAccessManager;
}

void ModuleWidget::generateModule(QList<QString> list)
{
    QString preUrl,params,strUrl;
    int i,size;
    i = 0;
    size = list.count();
    preUrl = QString("http://www.kegg.jp/kegg-bin/search_module_object?org_name=ko&amp;unclassified=");
    foreach (QString str, list) {
        i++;
        params.append(str.trimmed());
        if(i < size) {
            params.append("%20");
        }
    }
    strUrl = preUrl + params;
    ui->webView->load(QUrl(strUrl));
}
