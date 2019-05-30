#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include "parkwindow.h"

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
    void on_pbtlogout_clicked();
    void on_pbtset_clicked();
    void receiveData();
    void fun_register();
    void fun_about();
    void fun_init();
    void fun_useredit();

    void on_pbtpark_clicked();

    void on_pbtleave_clicked();

    void on_pbtsearch_clicked();

    void on_pbtbook_clicked();

private:
    Ui::MainWindow *ui;

public:
    int level=0;
    float feebig=0;
    float feesmall=0;
    int total=0;
    int book=0;
    int empty=0;
public:
    void refresh(void);
};

class parklot{
public:
    int level;
    float feebig;
    float feesmall;
    int total=0;
    int book=0;
    int empty=0;
};

#endif // MAINWINDOW_H
