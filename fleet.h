#ifndef FLEET_H
#define FLEET_H

#include <QObject>
#include "utilities.h"
#include "ship.h"

class fleet : public QObject
{
    public:
    Q_OBJECT
    int plshlf=0;                          //сколько кораблей у игрока
    int btshlf=0;                          //сколько кораблей у бота
    ship* bota;
    ship* playera;
public:
    explicit fleet(QObject *parent = nullptr);
    bool CheckDeath(int n, type in);
    bool CheckHit(int n, int x, int y, type in);
    void checkwinner();
    void createship(int x, int y, orientation os, int lenght, type in);
public slots:
     void CheckShip(int x, int y, type in);
     void setship(int x, int y, orientation os, int lenght, type in);
     void CleanPlShips();
signals:
    Q_SIGNAL void btshipdied(int x, int y, orientation os, int lenght);
    Q_SIGNAL void winn(type in);
    Q_SIGNAL void plshipdied();
};

#endif // FLEET_H
