#ifndef UTILITIES_H
#define UTILITIES_H

#include <QtWidgets>
#include <random>
#include "QTime"
//QTime midnight(0,0,0);
//qsrand(midnight.secsTo(QTime::currentTime()));

class utilities
{
public:
    utilities();
};

enum cell{clear, shipp, miss, desship, end, shipnearby};             //типы клетки
enum type{players, bots};                                       //типы поля
enum orientation{horizontal, vertical};                         //ориентация кораблей
enum route{righT, lefT, up, down};                              //нарпавления
enum gamestatus{botturn, playerturn};
enum status{Empty, Hit, Destroyed};

int generateRandomNumber(int from, int to);    //генерация ранодомного числа

#endif // UTILITIES_H
