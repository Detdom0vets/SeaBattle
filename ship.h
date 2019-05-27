#ifndef SHIP_H
#define SHIP_H

#include "utilities.h"

class ship
    {
    private:
        int x;                                           //координаты по x и y первой ячейки
        int y;
        orientation os;                                 //как расположен корабль
        int lenght;                                     //длина корабля
        bool mass[4]={0,0,0,0};                         //массив состояния клеток корабля (1-живб 0-подбит)
    public:
        bool CheckDeath();                                              //проверка умер ли
        void HitShip(int x, int y);                                     //получения ранения кораблем
        ship(int x, int y, orientation os, int lenght);
        ship();
        ship& operator= (const ship &Ship);
        void Reconstract(int x, int y, orientation os, int lenght);     //переназначение
        int rx();                                                       //возврат x
        int ry();                                                       //возврат y
        orientation ros();                                              //возврат os
        int rlenght();                                                  //возврат lenght

    };

#endif // SHIP_H

