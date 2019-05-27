#include "bot.h"

bot::bot()
{
    cellsleft=0;
    for (int i=1; i<11; i++)
    {
        for (int j=1; j<11; j++)
        {
           cellscoords[cellsleft][0]=i;  cellscoords[cellsleft][1]=j;
           cellsleft++;
        }
    }
}

void bot::TakeMap(cell* map)
{
    this->map=map;
}



void bot::shooting()
{
    int ff=cellsleft;
    srand((unsigned int)time(0));
    int t=rand()%ff;
    int x= cellscoords[t][1];
    int y= cellscoords[t][0];
    int x1, y1;
    x1=cellscoords[cellsleft-1][0]; y1=cellscoords[cellsleft-1][1];
    ff=cellsleft;
    cellscoords[cellsleft-1][0]=x; cellscoords[cellsleft-1][1]=y;
    cellscoords[t][0]=x1; cellscoords[t][1]=y1;
    cellsleft=ff-1;
    emit bshot(x, y);
}

void bot::lastturnwas(status tr)
{
    lastturn=tr;
}
