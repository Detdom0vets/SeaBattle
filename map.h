#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "utilities.h"
#include "ctime"
#include "fleet.h"

class Map : public QObject, public fleet
{
    public:
    Q_OBJECT
    public:
    cell field[12][12];                             //само поле состоящее из клеток


public:
    Map(int l);
    Map& operator= (const Map &map);                                                                        //перегрузка оператора присваивания
    bool CheckCanPut(int x, int y, orientation os, int lenght);                                             //проверка можно ли разместить корабль
    void SetNearbyShip(int x, int y);                                                                       //проверка можно ли разместить корабль по направлению
    void ShipPut(int x, int y, orientation os, int lenght);                                                 //размещение корабля                                                                //случайное размещение кораблей                                                                           //очистка карты
    explicit Map(QObject *parent = nullptr);

signals:
    Q_SIGNAL void Shotwas(status sta);                                                                      //отправка статуса прошлого выстрела
    Q_SIGNAL void SetShip(int x, int y, orientation os, int lenght);                                        //поставить корабль
    Q_SIGNAL void SendingMap(cell* field);                                                                  //отправка карты
    Q_SIGNAL void ShipDied(int x, int y, orientation os, int lenght);                                       //сообщить о смерти корабля
public slots:
     void MapRand();                                                                                        //рандом карты
     void Shot(int x, int y);                                                                               //выстрел
     void MapClear();                                                                                       //очистка карты
     void AreShipDead();                                                                                    //проверка погиб ли корабль
};
#endif // MAP_H
