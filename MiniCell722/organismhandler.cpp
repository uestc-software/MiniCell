#include "organismhandler.h"

OrganismHandler::OrganismHandler(QObject *parent) : QObject(parent)
{
    initOrganismMap();
}

OrganismHandler::~OrganismHandler()
{

}

void OrganismHandler::setOrganismMap(QMap<QString, QString> organismMap)
{
    this->organismMap = organismMap;
}

void OrganismHandler::initOrganismMap(){
    organismMap.insert(QString("aci"), QString("01"));
    organismMap.insert(QString("bsu"), QString("02"));
    organismMap.insert(QString("eco"), QString("03"));
    organismMap.insert(QString("ftn"), QString("04"));
    organismMap.insert(QString("hin"), QString("05"));
    organismMap.insert(QString("hpy"), QString("06"));
    organismMap.insert(QString("mge"), QString("07"));
    organismMap.insert(QString("mpu"), QString("08"));
    organismMap.insert(QString("mtu"), QString("09"));
    organismMap.insert(QString("pau"), QString("10"));
    organismMap.insert(QString("sao"), QString("11"));
    organismMap.insert(QString("spr"), QString("12"));
    organismMap.insert(QString("spu"), QString("13"));
    organismMap.insert(QString("stm"), QString("14"));
    organismMap.insert(QString("stt"), QString("15"));
    organismMap.insert(QString("vch"), QString("16"));
}

OrganismHandler::fetchOrganism(QMap<QString, QString> organismMap)
{
    this->organismMap = organismMap;
}

