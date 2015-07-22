#ifndef GENEHANDLER_H
#define GENEHANDLER_H

#include <QObject>

class GeneHandler : public QObject
{
    Q_OBJECT
public:
    explicit GeneHandler(QObject *parent = 0);
    ~GeneHandler();

    int status;
    void setStatus(int status);

    int total;
    void setTotal(int total);

    QList<QString> geneList;

    QList<int> countList;

signals:

public slots:
};
#endif // GENEHANDLER_H
