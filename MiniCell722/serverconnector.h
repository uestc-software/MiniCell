#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>
#include <QtNetwork>
#include <genehandler.h>
#include <organismhandler.h>

class ServerConnector : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnector(QObject *parent = 0);
    ~ServerConnector();

    GeneHandler *geneHdl;
    OrganismHandler *ogHdl;

    void callServer(QString url);

signals:

public slots:

private:
    QNetworkAccessManager *netManager;
    QJsonDocument jDoc;
    QJsonParseError jErr;

    void prepareNetManager();
    void initParam();
};

#endif // SERVERCONNECTOR_H
