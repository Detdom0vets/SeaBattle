#ifndef FLEET_H
#define FLEET_H

#include "utilities.h"
#include "ship.h"

class fleet
{
    public:
    int ShipsLeft=0;                            //сколько кораблей
    ship* Ships;                                //массив кораблей
    int x, y;                                   //корды, ориентация и длина погибшего корабля
    orientation os;
    int lenght;

public:
    fleet();
    ~fleet();
    void AddShipCount();                                            //добавить число кораблей
    void MinusShipCount();                                          //убавить число кораблей
    void MinusShip(int n);                                          //убрать корабль
    void CreateShip(int x, int y, orientation os, int lenght);      //создать корабль
    void SetHit(int x, int y);                                      //получение повреждений
    bool CheckShips();                                              //проверка кораблей
    void CleanShips();                                              //очистка кораблей
    int frx();                                                      //получения x
    int fry();                                                      //получения y
    orientation fros();                                             //получения os
    int frlenght();                                                 //получения lenght
};

#endif // FLEET_H
