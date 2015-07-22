#include "resultwidght.h"
#include "ui_resultwidght.h"
#include <organismhandler.h>

ResultWidght::ResultWidght(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidght)
{
    ui->setupUi(this);
    //set Layout to deal with Responsive Layout
    QGridLayout *resultLayout = new QGridLayout(this);
    resultLayout->addWidget(ui->gridLayoutWidget);
    //prepare network
    prepareNetManager();
    //set connect
    connect(netManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply_get_essential_gene(QNetworkReply*)));

    treeInit();
}

ResultWidght::~ResultWidght()
{
    delete ui;
}

void ResultWidght::callServer(QString strUrl)
{
    initPara();
    QNetworkRequest req;
    req.setUrl(QUrl(strUrl));
    netManager->get(req);
}

void ResultWidght::fetch_selected_data(QList<QString> list){
    orgaHandler = new OrganismHandler;
//    QString preUrl = QString("http://localhost/mCell/api/gene/index.php?id=");
    QString preUrl = QString("http://localhost/mccap-server/api/cegRecord/fetchCeg.php?id=");
    QString str,ids;
    foreach (str, list) {
        ids.append(orgaHandler->organismMap[str].trimmed());
    }
    QString url = preUrl + ids;
    qDebug() << url;
    callServer(url);
}

void ResultWidght::reply_get_essential_gene(QNetworkReply *reply)
{
    int status;
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString content = codec->toUnicode(reply->readAll());
    jDoc = QJsonDocument::fromJson(content.toUtf8(), &jError);
    if(jError.error == QJsonParseError::NoError) {
        if(jDoc.isObject()) {
            QVariantMap objMap = jDoc.toVariant().toMap();
            status = objMap["status"].toInt();
            if(!status) {
                qDebug() << status;
                QList<QVariant> dataList = objMap["data"].toList();
                for(int i = 0; i < dataList.size(); i++) {
                    QVariantMap data = dataList.at(i).toMap();
                    int category = data["category"].toInt();
                    QString cluster, description;
                    cluster = data["cluster"].toString();
                    description = data["description"].toString();
                    QStringList record;
                    record << cluster << description;
                    QTreeWidgetItem *node = ui->Browse->topLevelItem(category-1);
                    node->addChild(new QTreeWidgetItem(node, record));
                }
            }
        }
    }
}

//void ResultWidght::reply_get_essential_gene(QNetworkReply *reply)
//{
//    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QString all = codec->toUnicode(reply->readAll());
//    jDoc = QJsonDocument::fromJson(all.toUtf8(),&jError);
//    if(jError.error == QJsonParseError::NoError){
//        if(jDoc.isObject()){
//            QVariantMap objMap = jDoc.toVariant().toMap();
//            geneHandler->setStatus(objMap["status"].toInt());
//            if(!geneHandler->status){
//                geneHandler->setTotal(objMap["total"].toInt());
//                qDebug() << geneHandler->total;
//                for(int i=0;i<geneHandler->total;i++){
//                    geneHandler->geneList.append(objMap["gene_arr"].toList().at(i).toString());
//                    geneHandler->countList.append(objMap["count_arr"].toList().at(i).toInt());
//                }
//            }else{
//                qDebug() << "Status Err!";
//            }
//        }
//        ui->textBrowser->setText(all);
//    }else{
//        qFatal(jError.errorString().toUtf8().constData());
//        exit(1);
//    }
//}

void ResultWidght::prepareNetManager()
{
    netManager = new QNetworkAccessManager;
}

void ResultWidght::initPara()
{
    geneHandler = new GeneHandler;
}

void ResultWidght::treeInit()
{
    QStringList headerLab,cateName;
    headerLab << QObject::tr("Cluster of essential gene") << QObject::tr("Function description");
    ui->Browse->clear();
    ui->Browse->setColumnWidth(0, 300);
    ui->Browse->setColumnCount(2);
    ui->Browse->setHeaderLabels(headerLab);
    headerLab.clear();
    QTreeWidgetItem *category1 = new QTreeWidgetItem(ui->Browse, cateName << QObject::tr("Transport & Metabolism"));
    cateName.clear();
    QTreeWidgetItem *category2 = new QTreeWidgetItem(ui->Browse, cateName << QObject::tr("Transcription & Translation"));
    cateName.clear();
    QTreeWidgetItem *category3 = new QTreeWidgetItem(ui->Browse, cateName << QObject::tr("General function prediction only"));
    cateName.clear();
    QTreeWidgetItem *category4 = new QTreeWidgetItem(ui->Browse, cateName << QObject::tr("Function unknown"));
    cateName.clear();
    QTreeWidgetItem *category5 = new QTreeWidgetItem(ui->Browse, cateName << QObject::tr("Others"));
    cateName.clear();
    ui->Browse->addTopLevelItem(category1);
    ui->Browse->addTopLevelItem(category2);
    ui->Browse->addTopLevelItem(category3);
    ui->Browse->addTopLevelItem(category4);
    ui->Browse->addTopLevelItem(category5);
}
