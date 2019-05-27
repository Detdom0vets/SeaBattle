#include "fleet.h"

fleet::fleet()
{
    Ships = new ship[10];
}

fleet::~fleet()
{
    delete [] Ships;
    ShipsLeft=0;
}

void fleet::CreateShip(int x, int y, orientation os, int lenght)
{
    Ships[ShipsLeft].Reconstract(x,y,os,lenght);
    AddShipCount();
}

void fleet::AddShipCount()
{
    ShipsLeft++;
}

void fleet::MinusShipCount()
{
    ShipsLeft--;
}

bool fleet::CheckShips()
{
    for (int i=0; i<ShipsLeft; i++)
    {

       if (Ships[i].CheckDeath()) { this->x=Ships[i].rx(); this->y=Ships[i].ry(); this->os=Ships[i].ros(); this->lenght=Ships[i].rlenght(); MinusShip(i); return 1;}

    }
    return 0;
}

void fleet::MinusShip(int n)
{
    ship f1=Ships[ShipsLeft-1];
    Ships[ShipsLeft-1]=Ships[n];
    Ships[n]=f1;
    MinusShipCount();
}

void fleet::SetHit(int x, int y)
{
    for (int i=0; i<ShipsLeft; i++)
    {
        Ships[i].HitShip(x, y);
    }
}


void fleet::CleanShips()
{
    this->~fleet();
}

int fleet::frx()
{
    return x;
}

int fleet::fry()
{
    return y;
}

orientation fleet::fros()
{
    return os;
}

int fleet::frlenght()
{
    return lenght;
}
