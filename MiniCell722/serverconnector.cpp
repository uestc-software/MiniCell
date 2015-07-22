#include "serverconnector.h"

ServerConnector::ServerConnector(QObject *parent) : QObject(parent)
{
    prepareNetManager();
}

ServerConnector::~ServerConnector()
{

}

void ServerConnector::prepareNetManager()
{
    geneHdl = new GeneHandler;
}

void ServerConnector::initParam()
{
    netManager = new QNetworkAccessManager();
}

