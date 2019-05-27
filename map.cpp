#include "map.h"
#include "utilities.h"

Map::Map(int l)
{

    for (int i=1;i<11;++i)       //призначаем всем центральным ячейкам значение clear - незанятые
    {
        for (int j = 1; j < 11; ++j)
        {

            field[i][j] =clear;

        }
    }
    for (int j=0; j<12; ++j)
    {
        field[0][j]=end;
        field[11][j]=end;
        field[j][0]=end;
        field[j][11]=end;
    }

}

Map& Map::operator= (const Map &map)                                                        //перегрузка оператора присваивания
{
    for (int i=0; i<10; ++i)
    {
        for (int j=0; j<10; ++j)
        {
            this->field[i][j]=map.field[i][j];
        }
    }
    return *this;                                                                           //возвращаем ссылку на текущий объект
}


bool Map::CheckCanPut(int i, int j, orientation os, int lenght)             //проверка можно ли разместить корабль
{
    switch (os)
    {
    case horizontal:
        {
    for (int l=0; l<lenght; ++l)
    {
            if (field[j][i+l]!=clear) {return 0;}
    } break;
        }
    case vertical:
        {
        for (int l=0; l<lenght; ++l)
    {
        if (field[j+l][i]!=clear) {return 0;}
    } break;
        }
    }
    return 1;
}


void Map::SetNearbyShip(int i, int j)                             //проверка в радиусе 1 клетка
{

    if (field[i+1][j]==clear) {field[i+1][j]=shipnearby;}
    if (field[i+1][j+1]==clear) {field[i+1][j+1]=shipnearby;}
    if (field[i+1][j-1]==clear) {field[i+1][j-1]=shipnearby;}
    if (field[i-1][j+1]==clear) {field[i-1][j+1]=shipnearby;}
    if (field[i-1][j-1]==clear) {field[i-1][j-1]=shipnearby;}
    if (field[i-1][j]==clear) {field[i-1][j]=shipnearby;}
    if (field[i][j+1]==clear) {field[i][j+1]=shipnearby;}
    if (field[i][j-1]==clear) {field[i][j-1]=shipnearby;}
}


void Map::ShipPut(int x, int y, orientation os, int lenght)   //размещение корабля (принимает x, y коорды)
{
    for (int k=0; k<lenght; ++k)
    {
        if (os == horizontal) { field[y][x+k]=shipp; SetNearbyShip(y, x+k);}
        if (os == vertical) { field[y+k][x]=shipp; SetNearbyShip(y+k, x);}
    }
    this->CreateShip(x, y, os, lenght); emit SetShip(x, y, os, lenght);

}
void Map::Shot(int x, int y)                                                    //выстрел (приходят i , j - корды )
{
    switch (field[x][y])
{
    case clear: field[x][y]=miss; emit Shotwas(Empty); break;
    case shipnearby: field[x][y]=miss; emit Shotwas(Empty); break;
    case shipp: field[x][y]=desship; this->SetHit(y, x); emit Shotwas(Hit); break;
    default: break;
}
}

void Map::AreShipDead()
{
    if (this->CheckShips()) {emit ShipDied(this->frx(), this->fry(), this->fros(), this->frlenght());}
}

void Map::MapRand()                                                 //случайное размещение кораблей
{
    int lenght=4;
    int g=1;
    orientation os;
    for (int i=0; i<4; ++i)                                             //сначала генерируется положение для лмнкоров, потом крейсеров, потом есминцев и катеров
    {
        for (int j=0; j<g; ++j)
        {
            int t=8;
            do
            {
                srand((unsigned int)time(NULL));                                                                              //корабли утсанавливаются так, чтоб не выходить за границу поля
                int x=1+rand()%(10-lenght), y=1+rand()%10;
                int x1=1+rand()%10, y1=1+rand()%(10-lenght);
                bool e=rand()%2;
                if (e==1) {os=vertical;} else os=horizontal;
                switch (os)
                {
                case horizontal: if (CheckCanPut(x, y, os, lenght))                          //если CheckCanPut возвращяет 1, то размещяется корабль
                {
                    t=10;  ShipPut(x, y, os, lenght);
                }  break;
                case vertical: if (CheckCanPut(x1, y1, os, lenght))                          //если CheckCanPut возвращяет 1, то размещяется корабль
                    {
                        t=10;  ShipPut(x1, y1, os, lenght);
                    }  break;
                }

            }while (t!=10);

        }
        lenght--;
        g++;
    }
    emit SendingMap(*field);

}


void Map::MapClear()                                                            //очистка карты
{
    for (int i = 1; i < 10; ++i)
    {
        for (int j=1; j<10; ++j)
        {
            field[i][j]=clear;
        }
    }
    for (int j=0; j<12; ++j)
    {
        field[0][j]=end;
        field[11][j]=end;
        field[j][0]=end;
        field[j][11]=end;
    }
    this->CleanShips();
}


