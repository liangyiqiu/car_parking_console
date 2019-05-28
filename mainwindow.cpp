#include "mainwindow.h"
#include "loginwindow.h"
#include "setwindow.h"
#include "parkwindow.h"
#include "searchwindow.h"
#include "bookwindow.h"
#include "ui_mainwindow.h"
#include "leavewindow.h"
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    level=0;
    feebig=10.0;
    feesmall=5.0;
    total=1000;
    empty=200;
    book=100;
    ui->setupUi(this);
    MainWindow::setWin=new setWindow(this);
    connect(setWin,SIGNAL(sendData(Sdata)),this,SLOT(receiveData(Sdata)));
    connect(ui->actionlogout,SIGNAL(triggered()),this,SLOT(on_pbtlogout_clicked()));
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbtlogout_clicked()
{
    loginWindow *win = new loginWindow;
    win->show();
    this->close();
}



void MainWindow::on_pbtset_clicked()
{
    setWin->show();
}

void MainWindow::refresh()
{
    switch (level) {
    case 0:ui->lblevel->setText(QString::fromLocal8Bit("核心"));break;
    case 1:ui->lblevel->setText(QString::fromLocal8Bit("一级"));break;
    case 2:ui->lblevel->setText(QString::fromLocal8Bit("二级"));break;
    default:ui->lblevel->setText(QString::fromLocal8Bit("三级"));
    }

    ui->lbfeebig->setNum(feebig);
    ui->lbfeesmall->setNum(feesmall);
    ui->lbtotal->setNum(total);
    ui->lcdempty->display(empty);
    ui->lcdbook->display(book);
    ui->lcdleft->display(empty-book);
}

void MainWindow::receiveData(Sdata data)
{
    level=data.level;
    feebig=data.feebig;
    feesmall=data.feesmall;
    total=data.total;
    refresh();
    std::cout<<"received"<<std::endl;
}


void MainWindow::on_pbtpark_clicked()
{
    parkWindow *parkwin = new parkWindow;
    parkwin->show();
}

void MainWindow::on_pbtleave_clicked()
{
    leaveWindow *leavewin = new leaveWindow;
    leavewin->show();
}

void MainWindow::on_pbtsearch_clicked()
{
    searchWindow *searchwin = new searchWindow;
    searchwin->show();
}

void MainWindow::on_pbtbook_clicked()
{
    bookWindow *bookwin=new bookWindow;
    bookwin->show();
}
