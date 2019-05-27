#ifndef BOT_H
#define BOT_H

#include "QObject"
#include "utilities.h"
#include "ctime"

class bot : public QObject
{
    public:
    Q_OBJECT
    status lastturn;
    cell *map;
    int cellscoords[100][2];
    int cellsleft;
    public: bot();

public slots:
    void mapa(cell* map);
    void lastturnwas(status tr);
    void shooting();
signals:
    Q_SIGNAL void bshot(int x, int y);
};

#endif // BOT_H
