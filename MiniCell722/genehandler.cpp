#include "genehandler.h"

GeneHandler::GeneHandler(QObject *parent) : QObject(parent)
{

}

GeneHandler::~GeneHandler()
{

}

void GeneHandler::setStatus(int status)
{
    this->status = status;
}

void GeneHandler::setTotal(int total)
{
    this->total = total;
}
