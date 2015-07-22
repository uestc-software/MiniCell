#ifndef RESULTWIDGHT_H
#define RESULTWIDGHT_H

#include <QWidget>
#include <QtNetwork>
#include <genehandler.h>
#include <organismhandler.h>

namespace Ui {
class ResultWidght;
}

class ResultWidght : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidght(QWidget *parent = 0);
    ~ResultWidght();

    GeneHandler *geneHandler;
    OrganismHandler *orgaHandler;

    void callServer(QString strUrl);

public slots:
    void fetch_selected_data(QList<QString> list);
    void reply_get_essential_gene(QNetworkReply* reply);

private:
    Ui::ResultWidght *ui;
    QNetworkAccessManager *netManager;
    QJsonDocument jDoc,jDoc2;
    QJsonArray dataArr;
    QJsonParseError jError;

    void prepareNetManager();
    void initPara();
    void treeInit();
};

#endif // RESULTWIDGHT_H
