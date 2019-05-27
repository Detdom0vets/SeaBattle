#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "utilities.h"
#include "ctime"



class Map : public QObject
{
    public:
    Q_OBJECT
    public:
    cell field[12][12];                             //само поле состоящее из клеток


public:
    Map(int l);
    Map& operator= (const Map &map);                                                                    //перегрузка оператора присваивания
    bool CheckCanPut(int i, int j, orientation os, int shiplenght);                                    //проверка можно ли разместить корабль
    void SetNearbyShip(int i, int j);                                                                    //проверка можно ли разместить корабль по направлению
    void ShipPut(int i, int j, orientation os, int shiplenght);                                           //размещение корабля                                                                //случайное размещение кораблей                                                                           //очистка карты
    explicit Map(QObject *parent = nullptr);

signals:
    Q_SIGNAL void Shotwas(status sta);
    Q_SIGNAL void setship(int x, int y, orientation os, int lenght);
    Q_SIGNAL void sendingmap(cell* field);
public slots:
     void MapRandPlayer();
     void shot(int x, int y);
     void MapClear();


};

#endif // MAP_H
