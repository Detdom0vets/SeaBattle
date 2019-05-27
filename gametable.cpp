#include "gametable.h"
#include "ui_gametable.h"


GameTable::GameTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameTable)
{
    ui->setupUi(this);
    ui->label_closefield->setVisible(true);

    fleets= new fleet;
    //QObject::connect(fleets,SIGNAL(btshiphit(int, int, bool)),this,SLOT(bshot(int, int)));              //примает сигнал: координаты клетки корабля бота в которую попали и уничтожили ли его
    //QObject::connect(fleets,SIGNAL(plshiphit(int, int, bool)),this,SLOT(bshot(int, int)));              //примает сигнал: координаты клетки корабля игрока в которую попали и уничтожили ли его
    QObject::connect(fleets,SIGNAL(winn(type)),this,SLOT(havewinner(type)));                            //примает сигнал: что кто-то победил
    QObject::connect(this,SIGNAL(CheckShip(int, int, type)),fleets,SLOT(CheckShip(int, int, type)));    //отправляет сигнал: проверить корабли
    QObject::connect(fleets,SIGNAL(plshipdied()),this,SLOT(plshipdied()));                                                                     //примает сигнал: о смерти корабля игрока
    QObject::connect(fleets,SIGNAL(btshipdied(int, int, orientation, int)),this,SLOT(btshipdied(int, int, orientation, int)));                    //примает сигнал: о смерти корабля бота
    QObject::connect(this,SIGNAL(outsetship(int, int, orientation, int, type)),fleets,SLOT(setship(int, int, orientation, int, type)));         //отправляет сигнал: поставить корабль
    QObject::connect(this, SIGNAL(NeedClearMap()), fleets, SLOT(CleanPlShips()));                                                               //отправляет сигнал: очистить корабли игрока
    grisha = new bot();
    QObject::connect(grisha,SIGNAL(bshot(int, int)),this,SLOT(bbshot(int, int)));                                               //принимает сигнал: о выстреле бота
    QObject::connect(this,SIGNAL(sendMap(cell*)),grisha,SLOT(mapa(cell*)));                                                     //отправляет сигнал: карту игрока))
    QObject::connect(this,SIGNAL(sendlastturnwas(status)),grisha,SLOT(lastturnwas(status)));                                    //отправляет сигнал: попали ли бот
    QObject::connect(this,SIGNAL(sendCanShoot()),grisha, SLOT(shooting()));                                                     //отправляет сигнал: можно стрелять
    mapPl = new Map(10);
    QObject::connect(mapPl,SIGNAL(Shotwas(status)),this,SLOT(Shotwas(status)));                                                         //принимает сигнал: о выстреле
    QObject::connect(mapPl,SIGNAL(setship(int, int, orientation, int)),this,SLOT(plsetship(int, int, orientation, int)));               //принимает сигнал: поставть корабль(для флота)
    QObject::connect(mapPl,SIGNAL(sendingmap(cell*)),this,SLOT(takemap(cell*)));                                                        //принимает сигнал: карты игрока
    QObject::connect(this,SIGNAL(bsshot(int, int)),mapPl,SLOT(shot(int, int)));                                                 //отправляет сигнал: о выстреле
    QObject::connect(this,SIGNAL(MapRandPlayer()),mapPl,SLOT(MapRandPlayer()));                                                 //отправляет сигнал: сгенерировать карту
    QObject::connect(this, SIGNAL(NeedClearMap()), mapPl, SLOT(MapClear()));                                                    //отправляет сигнал: очистить карту
    emit MapRandPlayer();
    mapBt = new Map(10);
    QObject::connect(mapBt,SIGNAL(Shotwas(status)),this,SLOT(Shotwas(status)));                                                         //примает сигнал: поставить корабль (для флота)
    QObject::connect(mapBt,SIGNAL(setship(int, int, orientation, int)),this,SLOT(btsetship(int, int, orientation, int)));               //примает сигнал: о выстреле
    QObject::connect(this,SIGNAL(psshot(int, int)),mapBt,SLOT(shot(int, int)));                                                         //отправляет сигнал: выстрел игрока
    QObject::connect(this,SIGNAL(MapRandBot()),mapBt,SLOT(MapRandPlayer()));                                                         //отправляет сигнал: сгенерировать карту
    emit MapRandBot();
}

void GameTable::havewinner(type in)
{
    switch (in)
    {
    case bots: QMessageBox::information(this, "Победа", "Вы выиграли!"); on_menuMainmenu_triggered(); break;
    case players: QMessageBox::critical(this, "Поражение", "Вы проиграли!"); on_menuMainmenu_triggered(); break;
    }
}

void GameTable::takemap(cell* map)
{
    emit sendMap( map);
}

void GameTable::btsetship(int x, int y, orientation os, int lenght)             //постановка корабля бота для флота (x, y корды)
{
    emit outsetship( x,  y,  os,  lenght, bots);
}

void GameTable::plsetship(int x, int y, orientation os, int lenght)             //постановка корабля игрока  для флота (x, y корды)
{

    emit outsetship( x,  y,  os,  lenght, players);
    setship(x, y, os, lenght);
}

void GameTable::plshipdied()
{
    plship--;
    ui->leftplayership11->setNum(plship);
}

void GameTable::btshipdied(int x, int y, orientation os, int lenght)
{
    btship--;
    ui->leftbotship11->setNum(btship);
    switch (os)
    {
    case horizontal: for (int var = 0; var < lenght; ++var)
        {
            QPixmap kater(":/img/shiphit.png");
            int ff=countships;
            ships[countships].label= new QLabel(this);
            ships[countships].label->setPixmap(kater.scaled(32, 32,Qt::KeepAspectRatio)); ships[countships].label->move((468+35*(x+var-1)), (105+35*(y-1)));
            ships[countships].label->setMaximumWidth(32); ships[countships].label->setMaximumHeight(32);
            ships[countships].label->setVisible(true);
            countships=ff+1;
        } break;
    case vertical: for (int var = 0; var < lenght; ++var)
        {
            QPixmap kater(":/img/shiphit.png");
            int ff=countships;
            ships[countships].label= new QLabel(this);
            ships[countships].label->setPixmap(kater.scaled(32, 32,Qt::KeepAspectRatio)); ships[countships].label->move((468+35*(x-1)), (105+35*(y+var-1)));
            ships[countships].label->setMaximumWidth(32); ships[countships].label->setMaximumHeight(32);
            ships[countships].label->setVisible(true);
            countships=ff+1;
        } break;
    }
}

void GameTable::Shotwas(status tr)
{
    if (lastturn==bots) {sendlastturnwas(tr);}
    switch (tr)
    {
    case Hit: createHit(); if (lastturn==bots) {emit CheckShip(ib, jb, players); moveagain();} else {emit CheckShip(ip, jp, bots); moveagain();}  break;
    case Empty: createMiss(); passmove(); break;
    }
}

void GameTable::bbshot(int x, int y)                                //принимает ход бота
{
    ib=y; jb=x;
    lastturn=bots;
    emit bsshot( y,  x);                                            //отправляет ход бота карте игрока
}

void GameTable::passmove()
{
    switch (lastturn)
    {
    case bots: ui->label_closefield->setVisible(false);  break;
    case players: sendCanShoot();  break;
    }
}

void GameTable::moveagain()
{
    switch (lastturn)
    {
    case bots: sendCanShoot(); break;
    case players:  ui->label_closefield->setVisible(false); break;
    }
}

void GameTable::createMiss()
{
    switch (lastturn)
    {
        case bots:
    {
        QPixmap miss(":/img/miss.png");
        int ff=countbtfltx;
        botsfield[countbtfltx].label = new QLabel(this);
        botsfield[countbtfltx].label->setPixmap(miss.scaled(32, 32,Qt::KeepAspectRatio)); botsfield[countbtfltx].label->move((53+35*(jb-1)), (105+35*(ib-1)));
        botsfield[countbtfltx].label->setVisible(true);
        countbtfltx=ff+1;

    } break;
        case players:
    {
        QPixmap miss(":/img/miss.png");
        int ff=countplfltx;
        playersfield[countplfltx].label = new QLabel(this);
        playersfield[countplfltx].label->setPixmap(miss.scaled(32, 32,Qt::KeepAspectRatio)); playersfield[countplfltx].label->move((468+35*(jp-1)), (105+35*(ip-1)));
        playersfield[countplfltx].label->setMaximumWidth(32); playersfield[countplfltx].label->setMaximumHeight(32);
        playersfield[countplfltx].label->setVisible(true);
        countplfltx=ff+1;
    } break;
    }
}

void GameTable::createHit()
{
    switch (lastturn)
    {
        case bots:
    {
        QPixmap hit(":/img/shiphit.png");
        int ff=countbtfltx;
        botsfield[countbtfltx].label= new QLabel(this);
        botsfield[countbtfltx].label->setPixmap(hit.scaled(32, 32,Qt::KeepAspectRatio)); botsfield[countbtfltx].label->move((53+35*(jb-1)), (105+35*(ib-1)));
        botsfield[countbtfltx].label->setVisible(true);
        countbtfltx=ff+1;
    } break;
        case players:
    {
        QPixmap hit(":/img/hit.png");
        int ff=countplfltx;
        playersfield[countplfltx].label= new QLabel(this);
        playersfield[countplfltx].label->setPixmap(hit.scaled(32, 32,Qt::KeepAspectRatio)); playersfield[countplfltx].label->move((468+35*(jp-1)), (105+35*(ip-1)));
        playersfield[countplfltx].label->setMaximumWidth(32); playersfield[countplfltx].label->setMaximumHeight(32);
        playersfield[countplfltx].label->setVisible(true);
        countplfltx=ff+1;

    } break;
    }
}

GameTable::~GameTable()
{
    delete ui;
}



void GameTable::on_menuMainmenu_triggered()
{
    emit showmainwindow();
    QWidget::close();
}

void GameTable::on_menuSettings_triggered()
{
    Settings window;
    window.setModal(true);
    window.exec();
}

void GameTable::on_menuExit_triggered()
{
    QApplication::quit();
}


void GameTable::on_startbattlebutton_clicked()
{
    ui->label_closefield->setVisible(false);
    ui->startbattlebutton->setVisible(false);
    ui->replacebutton->setVisible(false);
}

void GameTable::on_replacebutton_clicked()
{
    emit NeedClearMap();
    for (int i=0; i<20; i++)
    {
        int ff=countships;
        delete ships[i].label;
        countships=ff-1;
    }
    emit MapRandPlayer();
}

void GameTable::setkater(int x, int y)
{
    QPixmap kater(":/img/shipcell.png");
    int ff=countships;
    ships[countships].label= new QLabel(this);
    ships[countships].label->setPixmap(kater.scaled(32, 32,Qt::KeepAspectRatio)); ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));
    countships=ff+1;
}

void GameTable::setship(int x, int y, orientation os, int lenght)
{
    switch (os)
    {
    case horizontal: for (int var = 0; var < lenght; ++var)
        {
            setkater(x+var,y);
        } break;
    case vertical: for (int var = 0; var < lenght; ++var)
        {
            setkater(x,y+var);
        } break;
    }
}

/*
void GameTable::setlinkor(int x, int y,orientation os)
{
    QPixmap linkor(":/img/linkorV.png");
    QPixmap linkorV(":/img/linkor.png");
    ships[countships].label= new QLabel(this);
    if (os==horizontal) {ships[countships].label->setPixmap(linkor.scaled(137, 32,Qt::IgnoreAspectRatio));ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));}
    else {ships[countships].label->setPixmap(linkorV.scaled(32, 137,Qt::IgnoreAspectRatio)); ships[countships].label->move((53+35*(x-1)), (103+35*(y-1)));}
    countships++;
}

void GameTable::setkreiser(int x, int y,orientation os)
{
    QPixmap kreiser(":/img/kreiserV.png");
    QPixmap kreiserV(":/img/kreiser.png");
    ships[countships].label= new QLabel(this);
    if (os==horizontal) {ships[countships].label->setPixmap(kreiser.scaled(102, 32,Qt::IgnoreAspectRatio)); ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));}
    else {ships[countships].label->setPixmap(kreiserV.scaled(32, 102,Qt::IgnoreAspectRatio)); ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));}
    countships++;
}

void GameTable::setesminec(int x, int y,orientation os)
{
    QPixmap esminec(":/img/esminec.png");
    QPixmap esminecV(":/img/esminecV.png");
    ships[countships].label= new QLabel(this);
    if (os==horizontal) {ships[countships].label->setPixmap(esminec.scaled(67, 32,Qt::IgnoreAspectRatio)); ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));}
    else {ships[countships].label->setPixmap(esminecV.scaled(32, 67,Qt::IgnoreAspectRatio)); ships[countships].label->move((53+35*(x-1)), (105+35*(y-1)));}
    countships++;
 }
*/

/*
void GameTable::setship(int x, int y, orientation os, int lenght)
{
        switch (lenght)                                 //корабли раставляются в зависомоти от их ориентации и длины
        {
        case 4: setlinkor(x, y, os); break;
        case 3: setkreiser(x, y, os); break;
        case 2: setesminec(x, y, os); break;
        case 1: setkater(x, y); break;
        }
}
*/



void GameTable::on_pushButton_1_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_1->setVisible(false);
        ip = 1;
        jp = 1;
        lastturn = players;
        emit psshot( 1, 1 );
}
void GameTable::on_pushButton_2_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_2->setVisible(false);
        ip = 1;
        jp = 2;
        lastturn = players;
        emit psshot( 1, 2 );
}
void GameTable::on_pushButton_3_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_3->setVisible(false);
        ip = 1;
        jp = 3;
        lastturn = players;
        emit psshot( 1, 3 );
}
void GameTable::on_pushButton_4_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ip = 1;
        jp = 4;
        lastturn = players;
        emit psshot( 1, 4 );
}
void GameTable::on_pushButton_5_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_5->setVisible(false);
        ip = 1;
        jp = 5;
        lastturn = players;
        emit psshot( 1, 5 );
}
void GameTable::on_pushButton_6_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_6->setVisible(false);
        ip = 1;
        jp = 6;
        lastturn = players;
        emit psshot( 1, 6 );
}
void GameTable::on_pushButton_7_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_7->setVisible(false);
        ip = 1;
        jp = 7;
        lastturn = players;
        emit psshot( 1, 7 );
}
void GameTable::on_pushButton_8_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_8->setVisible(false);
        ip = 1;
        jp = 8;
        lastturn = players;
        emit psshot( 1, 8 );
}
void GameTable::on_pushButton_9_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_9->setVisible(false);
        ip = 1;
        jp = 9;
        lastturn = players;
        emit psshot( 1, 9 );
}
void GameTable::on_pushButton_10_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_10->setVisible(false);
        ip = 1;
        jp = 10;
        lastturn = players;
        emit psshot( 1, 10 );
}
void GameTable::on_pushButton_11_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_11->setVisible(false);
        ip = 2;
        jp = 1;
        lastturn = players;
        emit psshot( 2, 1 );
}
void GameTable::on_pushButton_12_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_12->setVisible(false);
        ip = 2;
        jp = 2;
        lastturn = players;
        emit psshot( 2, 2 );
}
void GameTable::on_pushButton_13_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_13->setVisible(false);
        ip = 2;
        jp = 3;
        lastturn = players;
        emit psshot( 2, 3 );
}
void GameTable::on_pushButton_14_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_14->setVisible(false);
        ip = 2;
        jp = 4;
        lastturn = players;
        emit psshot( 2, 4 );
}
void GameTable::on_pushButton_15_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_15->setVisible(false);
        ip = 2;
        jp = 5;
        lastturn = players;
        emit psshot( 2, 5 );
}
void GameTable::on_pushButton_16_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_16->setVisible(false);
        ip = 2;
        jp = 6;
        lastturn = players;
        emit psshot( 2, 6 );
}
void GameTable::on_pushButton_17_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_17->setVisible(false);
        ip = 2;
        jp = 7;
        lastturn = players;
        emit psshot( 2, 7 );
}
void GameTable::on_pushButton_18_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_18->setVisible(false);
        ip = 2;
        jp = 8;
        lastturn = players;
        emit psshot( 2, 8 );
}
void GameTable::on_pushButton_19_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_19->setVisible(false);
        ip = 2;
        jp = 9;
        lastturn = players;
        emit psshot( 2, 9 );
}
void GameTable::on_pushButton_20_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_20->setVisible(false);
        ip = 2;
        jp = 10;
        lastturn = players;
        emit psshot( 2, 10 );
}
void GameTable::on_pushButton_21_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_21->setVisible(false);
        ip = 3;
        jp = 1;
        lastturn = players;
        emit psshot( 3, 1 );
}
void GameTable::on_pushButton_22_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_22->setVisible(false);
        ip = 3;
        jp = 2;
        lastturn = players;
        emit psshot( 3, 2 );
}
void GameTable::on_pushButton_23_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_23->setVisible(false);
        ip = 3;
        jp = 3;
        lastturn = players;
        emit psshot( 3, 3 );
}
void GameTable::on_pushButton_24_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_24->setVisible(false);
        ip = 3;
        jp = 4;
        lastturn = players;
        emit psshot( 3, 4 );
}
void GameTable::on_pushButton_25_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_25->setVisible(false);
        ip = 3;
        jp = 5;
        lastturn = players;
        emit psshot( 3, 5 );
}
void GameTable::on_pushButton_26_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_26->setVisible(false);
        ip = 3;
        jp = 6;
        lastturn = players;
        emit psshot( 3, 6 );
}
void GameTable::on_pushButton_27_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_27->setVisible(false);
        ip = 3;
        jp = 7;
        lastturn = players;
        emit psshot( 3, 7 );
}
void GameTable::on_pushButton_28_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_28->setVisible(false);
        ip = 3;
        jp = 8;
        lastturn = players;
        emit psshot( 3, 8 );
}
void GameTable::on_pushButton_29_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_29->setVisible(false);
        ip = 3;
        jp = 9;
        lastturn = players;
        emit psshot( 3, 9 );
}
void GameTable::on_pushButton_30_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_30->setVisible(false);
        ip = 3;
        jp = 10;
        lastturn = players;
        emit psshot( 3, 10 );
}
void GameTable::on_pushButton_31_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_31->setVisible(false);
        ip = 4;
        jp = 1;
        lastturn = players;
        emit psshot( 4, 1 );
}
void GameTable::on_pushButton_32_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_32->setVisible(false);
        ip = 4;
        jp = 2;
        lastturn = players;
        emit psshot( 4, 2 );
}
void GameTable::on_pushButton_33_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_33->setVisible(false);
        ip = 4;
        jp = 3;
        lastturn = players;
        emit psshot( 4, 3 );
}
void GameTable::on_pushButton_34_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_34->setVisible(false);
        ip = 4;
        jp = 4;
        lastturn = players;
        emit psshot( 4, 4 );
}
void GameTable::on_pushButton_35_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_35->setVisible(false);
        ip = 4;
        jp = 5;
        lastturn = players;
        emit psshot( 4, 5 );
}
void GameTable::on_pushButton_36_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_36->setVisible(false);
        ip = 4;
        jp = 6;
        lastturn = players;
        emit psshot( 4, 6 );
}
void GameTable::on_pushButton_37_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_37->setVisible(false);
        ip = 4;
        jp = 7;
        lastturn = players;
        emit psshot( 4, 7 );
}
void GameTable::on_pushButton_38_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_38->setVisible(false);
        ip = 4;
        jp = 8;
        lastturn = players;
        emit psshot( 4, 8 );
}
void GameTable::on_pushButton_39_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_39->setVisible(false);
        ip = 4;
        jp = 9;
        lastturn = players;
        emit psshot( 4, 9 );
}
void GameTable::on_pushButton_40_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_40->setVisible(false);
        ip = 4;
        jp = 10;
        lastturn = players;
        emit psshot( 4, 10 );
}
void GameTable::on_pushButton_41_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_41->setVisible(false);
        ip = 5;
        jp = 1;
        lastturn = players;
        emit psshot( 5, 1 );
}
void GameTable::on_pushButton_42_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_42->setVisible(false);
        ip = 5;
        jp = 2;
        lastturn = players;
        emit psshot( 5, 2 );
}
void GameTable::on_pushButton_43_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_43->setVisible(false);
        ip = 5;
        jp = 3;
        lastturn = players;
        emit psshot( 5, 3 );
}
void GameTable::on_pushButton_44_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_44->setVisible(false);
        ip = 5;
        jp = 4;
        lastturn = players;
        emit psshot( 5, 4 );
}
void GameTable::on_pushButton_45_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_45->setVisible(false);
        ip = 5;
        jp = 5;
        lastturn = players;
        emit psshot( 5, 5 );
}
void GameTable::on_pushButton_46_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_46->setVisible(false);
        ip = 5;
        jp = 6;
        lastturn = players;
        emit psshot( 5, 6 );
}
void GameTable::on_pushButton_47_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_47->setVisible(false);
        ip = 5;
        jp = 7;
        lastturn = players;
        emit psshot( 5, 7 );
}
void GameTable::on_pushButton_48_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_48->setVisible(false);
        ip = 5;
        jp = 8;
        lastturn = players;
        emit psshot( 5, 8 );
}
void GameTable::on_pushButton_49_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_49->setVisible(false);
        ip = 5;
        jp = 9;
        lastturn = players;
        emit psshot( 5, 9 );
}
void GameTable::on_pushButton_50_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_50->setVisible(false);
        ip = 5;
        jp = 10;
        lastturn = players;
        emit psshot( 5, 10 );
}
void GameTable::on_pushButton_51_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_51->setVisible(false);
        ip = 6;
        jp = 1;
        lastturn = players;
        emit psshot( 6, 1 );
}
void GameTable::on_pushButton_52_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_52->setVisible(false);
        ip = 6;
        jp = 2;
        lastturn = players;
        emit psshot( 6, 2 );
}
void GameTable::on_pushButton_53_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_53->setVisible(false);
        ip = 6;
        jp = 3;
        lastturn = players;
        emit psshot( 6, 3 );
}
void GameTable::on_pushButton_54_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_54->setVisible(false);
        ip = 6;
        jp = 4;
        lastturn = players;
        emit psshot( 6, 4 );
}
void GameTable::on_pushButton_55_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_55->setVisible(false);
        ip = 6;
        jp = 5;
        lastturn = players;
        emit psshot( 6, 5 );
}
void GameTable::on_pushButton_56_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_56->setVisible(false);
        ip = 6;
        jp = 6;
        lastturn = players;
        emit psshot( 6, 6 );
}
void GameTable::on_pushButton_57_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_57->setVisible(false);
        ip = 6;
        jp = 7;
        lastturn = players;
        emit psshot( 6, 7 );
}
void GameTable::on_pushButton_58_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_58->setVisible(false);
        ip = 6;
        jp = 8;
        lastturn = players;
        emit psshot( 6, 8 );
}
void GameTable::on_pushButton_59_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_59->setVisible(false);
        ip = 6;
        jp = 9;
        lastturn = players;
        emit psshot( 6, 9 );
}
void GameTable::on_pushButton_60_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_60->setVisible(false);
        ip = 6;
        jp = 10;
        lastturn = players;
        emit psshot( 6, 10 );
}
void GameTable::on_pushButton_61_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_61->setVisible(false);
        ip = 7;
        jp = 1;
        lastturn = players;
        emit psshot( 7, 1 );
}
void GameTable::on_pushButton_62_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_62->setVisible(false);
        ip = 7;
        jp = 2;
        lastturn = players;
        emit psshot( 7, 2 );
}
void GameTable::on_pushButton_63_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_63->setVisible(false);
        ip = 7;
        jp = 3;
        lastturn = players;
        emit psshot( 7, 3 );
}
void GameTable::on_pushButton_64_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_64->setVisible(false);
        ip = 7;
        jp = 4;
        lastturn = players;
        emit psshot( 7, 4 );
}
void GameTable::on_pushButton_65_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_65->setVisible(false);
        ip = 7;
        jp = 5;
        lastturn = players;
        emit psshot( 7, 5 );
}
void GameTable::on_pushButton_66_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_66->setVisible(false);
        ip = 7;
        jp = 6;
        lastturn = players;
        emit psshot( 7, 6 );
}
void GameTable::on_pushButton_67_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_67->setVisible(false);
        ip = 7;
        jp = 7;
        lastturn = players;
        emit psshot( 7, 7 );
}
void GameTable::on_pushButton_68_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_68->setVisible(false);
        ip = 7;
        jp = 8;
        lastturn = players;
        emit psshot( 7, 8 );
}
void GameTable::on_pushButton_69_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_69->setVisible(false);
        ip = 7;
        jp = 9;
        lastturn = players;
        emit psshot( 7, 9 );
}
void GameTable::on_pushButton_70_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_70->setVisible(false);
        ip = 7;
        jp = 10;
        lastturn = players;
        emit psshot( 7, 10 );
}
void GameTable::on_pushButton_71_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_71->setVisible(false);
        ip = 8;
        jp = 1;
        lastturn = players;
        emit psshot( 8, 1 );
}
void GameTable::on_pushButton_72_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_72->setVisible(false);
        ip = 8;
        jp = 2;
        lastturn = players;
        emit psshot( 8, 2 );
}
void GameTable::on_pushButton_73_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_73->setVisible(false);
        ip = 8;
        jp = 3;
        lastturn = players;
        emit psshot( 8, 3 );
}
void GameTable::on_pushButton_74_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_74->setVisible(false);
        ip = 8;
        jp = 4;
        lastturn = players;
        emit psshot( 8, 4 );
}
void GameTable::on_pushButton_75_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_75->setVisible(false);
        ip = 8;
        jp = 5;
        lastturn = players;
        emit psshot( 8, 5 );
}
void GameTable::on_pushButton_76_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_76->setVisible(false);
        ip = 8;
        jp = 6;
        lastturn = players;
        emit psshot( 8, 6 );
}
void GameTable::on_pushButton_77_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_77->setVisible(false);
        ip = 8;
        jp = 7;
        lastturn = players;
        emit psshot( 8, 7 );
}
void GameTable::on_pushButton_78_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_78->setVisible(false);
        ip = 8;
        jp = 8;
        lastturn = players;
        emit psshot( 8, 8 );
}
void GameTable::on_pushButton_79_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_79->setVisible(false);
        ip = 8;
        jp = 9;
        lastturn = players;
        emit psshot( 8, 9 );
}
void GameTable::on_pushButton_80_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_80->setVisible(false);
        ip = 8;
        jp = 10;
        lastturn = players;
        emit psshot( 8, 10 );
}
void GameTable::on_pushButton_81_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_81->setVisible(false);
        ip = 9;
        jp = 1;
        lastturn = players;
        emit psshot( 9, 1 );
}
void GameTable::on_pushButton_82_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_82->setVisible(false);
        ip = 9;
        jp = 2;
        lastturn = players;
        emit psshot( 9, 2 );
}
void GameTable::on_pushButton_83_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_83->setVisible(false);
        ip = 9;
        jp = 3;
        lastturn = players;
        emit psshot( 9, 3 );
}
void GameTable::on_pushButton_84_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_84->setVisible(false);
        ip = 9;
        jp = 4;
        lastturn = players;
        emit psshot( 9, 4 );
}
void GameTable::on_pushButton_85_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_85->setVisible(false);
        ip = 9;
        jp = 5;
        lastturn = players;
        emit psshot( 9, 5 );
}
void GameTable::on_pushButton_86_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_86->setVisible(false);
        ip = 9;
        jp = 6;
        lastturn = players;
        emit psshot( 9, 6 );
}
void GameTable::on_pushButton_87_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_87->setVisible(false);
        ip = 9;
        jp = 7;
        lastturn = players;
        emit psshot( 9, 7 );
}
void GameTable::on_pushButton_88_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_88->setVisible(false);
        ip = 9;
        jp = 8;
        lastturn = players;
        emit psshot( 9, 8 );
}
void GameTable::on_pushButton_89_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_89->setVisible(false);
        ip = 9;
        jp = 9;
        lastturn = players;
        emit psshot( 9, 9 );
}
void GameTable::on_pushButton_90_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_90->setVisible(false);
        ip = 9;
        jp = 10;
        lastturn = players;
        emit psshot( 9, 10 );
}
void GameTable::on_pushButton_91_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_91->setVisible(false);
        ip = 10;
        jp = 1;
        lastturn = players;
        emit psshot( 10, 1 );
}
void GameTable::on_pushButton_92_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_92->setVisible(false);
        ip = 10;
        jp = 2;
        lastturn = players;
        emit psshot( 10, 2 );
}
void GameTable::on_pushButton_93_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_93->setVisible(false);
        ip = 10;
        jp = 3;
        lastturn = players;
        emit psshot( 10, 3 );
}
void GameTable::on_pushButton_94_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_94->setVisible(false);
        ip = 10;
        jp = 4;
        lastturn = players;
        emit psshot( 10, 4 );
}
void GameTable::on_pushButton_95_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_95->setVisible(false);
        ip = 10;
        jp = 5;
        lastturn = players;
        emit psshot( 10, 5 );
}
void GameTable::on_pushButton_96_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_96->setVisible(false);
        ip = 10;
        jp = 6;
        lastturn = players;
        emit psshot( 10, 6 );
}
void GameTable::on_pushButton_97_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_97->setVisible(false);
        ip = 10;
        jp = 7;
        lastturn = players;
        emit psshot( 10, 7 );
}
void GameTable::on_pushButton_98_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_98->setVisible(false);
        ip = 10;
        jp = 8;
        lastturn = players;
        emit psshot( 10, 8 );
}
void GameTable::on_pushButton_99_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_99->setVisible(false);
        ip = 10;
        jp = 9;
        lastturn = players;
        emit psshot( 10, 9 );
}
void GameTable::on_pushButton_100_clicked()
{
        ui->label_closefield->setVisible(true);
        ui->pushButton_100->setVisible(false);
        ip = 10;
        jp = 10;
        lastturn = players;
        emit psshot( 10, 10 );
}
