#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "gametable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menuExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_menuSettings_triggered()
{
    Settings window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_Exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_Start_clicked()
{
    GameTable *table= new GameTable();
    connect(table, SIGNAL(showmainwindow()), this, SLOT(showwindow()));
    table->show();
    this->hide();
}

void MainWindow::on_menuplay_triggered()
{
    GameTable *table= new GameTable;
    table->show();
}

void MainWindow::showwindow()
{
    this->show();
}

