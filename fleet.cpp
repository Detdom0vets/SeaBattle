#include "fleet.h"

fleet::fleet(QObject *parent) : QObject(parent)
{
    bota = new ship[10];
    playera = new ship[10];
}

void fleet::createship(int x, int y, orientation os, int lenght, type in)           //принимает x, y коорды
{
    switch (in)
    {
    case bots:
      {
        int ff=btshlf;
        bota[btshlf].reconstract(x,y,os,lenght);
        btshlf=ff+1;
        break;}
    case players:
    {
        int ff=plshlf;
        playera[plshlf].reconstract(x,y,os,lenght);
        plshlf=ff+1;
        break;}
    }
}

void fleet::checkwinner()
{
    if (plshlf==0) {emit winn(players);}
    if (btshlf==0) {emit winn(bots);}
}

void fleet::setship(int x, int y, orientation os, int lenght, type in)
{
    switch (in)
    {
    case bots: createship(x, y, os, lenght, in); break;
    case players: createship(x, y, os, lenght, in); break;
    }
}

void fleet::CheckShip(int x, int y, type in)                //проверка кораблей (принимает i, j коорды)
{
    switch (in)
    {
    case players: for (int i=0; i<10; i++)
        {
            if (playera[i].checkhit(y, x))
                {emit plshipdied(); plshlf--; checkwinner();}
        } break;
    case bots: for (int i=0; i<10; i++)
        {
            if (bota[i].checkhit( y, x))
                {emit btshipdied(bota[i].rx(), bota[i].ry(), bota[i].ros(), bota[i].rlenght());
                    btshlf--; checkwinner();}
        } break;
    }
}


void fleet::CleanPlShips()
{
    plshlf=0;
}
