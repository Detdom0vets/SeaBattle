#ifndef BOT_H
#define BOT_H

#include "QObject"
#include "utilities.h"
#include "ctime"

class bot : public QObject
{
    public:
    Q_OBJECT
    status lastturn;                    //попали или нет в прошлый раз бот
    cell *map;                          //карта игрока
    int cellscoords[100][2];            //корды чистых ячеек
    int cellsleft;                      //количество свободных ячеек
    public: bot();

public slots:
    void TakeMap(cell* map);            //взятие карты игрока
    void lastturnwas(status tr);        //взятия состояния ячейки прошлого выстрела
    void shooting();                    //получение разршения стрелять
signals:
    Q_SIGNAL void bshot(int x, int y);  //отправка ячеек в которые стреляет
};

#endif // BOT_H
