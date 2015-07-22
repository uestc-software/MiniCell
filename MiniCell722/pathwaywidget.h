#ifndef PATHWAYWIDGET_H
#define PATHWAYWIDGET_H

#include <QWidget>
#include <QtWebKitWidgets/QWebView>
#include <QtNetwork>
#include <organismhandler.h>

namespace Ui {
class PathwayWidget;
}

class PathwayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PathwayWidget(QWidget *parent = 0);
    ~PathwayWidget();

    OrganismHandler *orgaHandler;

    void callServer(QString strUrl);

public slots:
    void fetch_selected_data_pw(QList<QString> list);
    void reply_show_pathway(QNetworkReply* reply);

private slots:
    void on_webView_linkClicked(const QUrl &arg1);

private:
    Ui::PathwayWidget *ui;
    QNetworkAccessManager *netManager;
    QJsonDocument jDoc;
    QJsonParseError jError;

    void prepareNetManager();
    void generatePathway(QList<QString> list);
};

#endif // PATHWAYWIDGET_H
