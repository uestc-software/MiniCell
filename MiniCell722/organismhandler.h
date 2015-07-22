#ifndef OGANISMHANDLER_H
#define OGANISMHANDLER_H

#include <QObject>
#include <QMap>

class OrganismHandler : public QObject
{
    Q_OBJECT
public:
    explicit OrganismHandler(QObject *parent = 0);
    ~OrganismHandler();

    QMap<QString, QString> organismMap;
    void setOrganismMap(QMap<QString, QString> organismMap);

    void initOrganismMap();

signals:

public slots:
    fetchOrganism(QMap<QString, QString> organismMap);
};

#endif // OGANISMHANDLER_H
