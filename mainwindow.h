#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showwindow();

    void on_menuExit_triggered();

    void on_menuSettings_triggered();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Start_clicked();

    void on_menuplay_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
