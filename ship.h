#ifndef SHIP_H
#define SHIP_H

#include <QObject>
#include "utilities.h"


class ship
    {
    private:
        int x;                  //координаты по x и y первой ячейки
        int y;
        orientation os;               //как расположен корабль
        int lenght;                          //длина корабля
        bool mass[4]={0,0,0,0};             //массив состояния клеток корабля (1-живб 0-подбит)
    public:
        bool CheckDeath();
        bool checkhit(int x, int y);
        ship(int x, int y, orientation os, int lenght);
        ship();
        ship& operator= (const ship &Ship);
        void reconstract(int x, int y, orientation os, int lenght);
        int rx();
        int ry();
        orientation ros();
        int rlenght();

    };

#endif // SHIP_H

