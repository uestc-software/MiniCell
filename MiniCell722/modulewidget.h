#ifndef MODULEWIDGET_H
#define MODULEWIDGET_H

#include <QWidget>
#include <QtWebKitWidgets/QWebView>
#include <QtNetwork>
#include <organismhandler.h>

namespace Ui {
class ModuleWidget;
}

class ModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleWidget(QWidget *parent = 0);
    ~ModuleWidget();

    OrganismHandler *orgaHandler;

    void callServer(QString strUrl);

public slots:
    void fetch_selected_data_md(QList<QString> list);
    void reply_show_module(QNetworkReply* reply);

private slots:
    void on_webView_linkClicked(const QUrl url);

private:
    Ui::ModuleWidget *ui;
    QNetworkAccessManager *netManager;
    QJsonDocument jDoc;
    QJsonParseError jError;

    void prepareNetManager();
    void generateModule(QList<QString> list);
};

#endif // MODULEWIDGET_H
