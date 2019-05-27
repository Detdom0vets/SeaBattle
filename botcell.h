#ifndef BOTCELL_H
#define BOTCELL_H

#include "QPushButton"

class botcell : public QPushButton
{
public:
    QPushButton *arr;
    botcell(int x, int y);
};

#endif // BOTCELL_H
