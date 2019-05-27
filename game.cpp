#include "game.h"
#include "QLabel"
#include "utilities.h"


/*
game::game()
{
    font->setPointSize(16);                         //шрифт 16 размера
    font->setBold(0);
    QLabel *leftplayership = new QLabel("10");
    leftplayership->move(248, 0);                   //рамещение лейбла на х:248 у:0 ; с размером 21 на 41 и шрифтом font
    leftplayership->setBaseSize(21, 41);
    leftplayership->setFont(*font);
    QLabel *leftbotship = new QLabel("10");
    leftbotship->setBaseSize(21, 41);
    leftbotship->move(818, 0);
    leftbotship->setFont(*font);
    plfield = new QLabel [10];

}

game::~game()
{
        delete [] plfield;
}

game& game::operator= (const game &Game)                                                           //перегрузка оператора присваивания
{
    font=Game.font;
    leftplayership=Game.leftplayership;
    leftbotship=Game.leftbotship;
    plfield = Game.plfield;
    plshlf=Game.plshlf;
    btshlf=Game.btshlf;
    lab=Game.lab;
    return *this;
}

void game::PlayerShip()                   // -1 корабль у игрока
{
   leftplayership->setNum(plshlf-1);
}

void game::BotShip()                       // -1 корабль у бота
{
    leftbotship->setNum(btshlf-1);
}

bool game::AreShipsLeft()                  // Проверка остались ли корабли
{
    if(plshlf!=0 && btshlf!=0) {return 1;}
    else return 0;
}

void game::CreateShip(int i, int j, orientation in, int shiplenght)
{
    QPixmap linkor(":/img/linkor.png");
    QPixmap linkorV(":/img/linkorV.png");
    QPixmap kreiser(":/img/kreiser.png");
    QPixmap kreiserV(":/img/kreiserV.png");
    QPixmap esminec(":/img/esminec.png");
    QPixmap esminecV(":/img/esminecV.png");
    QPixmap kater(":/img/kater.png");
    switch (shiplenght)                                 //корабли раставляются в зависомоти от их ориентации и длины
    {
    case 4: if (in==horizontal) {plfield[lab].setPixmap(linkor); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 128, 31); lab++;} else {plfield[lab].setPixmap(linkorV); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 31, 128); lab++;} break;
    case 3: if (in==horizontal) {plfield[lab].setPixmap(kreiser); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 97 , 32); lab++;} else {plfield[lab].setPixmap(kreiserV); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 32 , 97); lab++;} break;
    case 2: if (in==horizontal) {plfield[lab].setPixmap(esminec); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 65, 33);lab++;} else {plfield[lab].setPixmap(esminecV); plfield[lab].setGeometry((76+38*(i+1)), (38*(j+1)), 33, 65); lab++;} break;
    case 1: {plfield[lab].setPixmap(kater); plfield[lab].setGeometry((76*(i+1)), (38*(i+1)), 33, 31); lab++;} break;
    }
}
*/
