#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    setWindow *setWin;

private slots:
    void on_pbtlogout_clicked();
    void on_pbtset_clicked();
    void receiveData(Sdata);

    void on_pbtpark_clicked();

    void on_pbtleave_clicked();

    void on_pbtsearch_clicked();

    void on_pbtbook_clicked();

private:
    Ui::MainWindow *ui;

public:
    int level;
    float feebig;
    float feesmall;
    int total;
    int book;
    int empty;
public:
    void refresh(void);
};

#endif // MAINWINDOW_H
