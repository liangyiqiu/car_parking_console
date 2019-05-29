#include "mainwindow.h"
#include "loginwindow.h"
#include "setwindow.h"
#include "parkwindow.h"
#include "searchwindow.h"
#include "bookwindow.h"
#include "ui_mainwindow.h"
#include "leavewindow.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    setWindow *setWin=new setWindow(this);
    connect(setWin,SIGNAL(sendData()),this,SLOT(receiveData()));
    setWin->show();
}


void MainWindow::on_pbtpark_clicked()
{
    parkWindow *parkwin=new parkWindow(this);
    connect(parkwin,SIGNAL(sendData()),this,SLOT(receiveData()));
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

void MainWindow::refresh()
{
    class parklot parklot0;
    ifstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile) {
        cout << "Source file open error." << endl;
    }
    else
    {
        while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
        inFile.close();
    }

    switch (parklot0.level) {
    case 0:ui->lblevel->setText(QString::fromLocal8Bit("核心"));break;
    case 1:ui->lblevel->setText(QString::fromLocal8Bit("一级"));break;
    case 2:ui->lblevel->setText(QString::fromLocal8Bit("二级"));break;
    default:ui->lblevel->setText(QString::fromLocal8Bit("三级"));
    }

    ui->lbfeebig->setNum(parklot0.feebig);
    ui->lbfeesmall->setNum(parklot0.feesmall);
    ui->lbtotal->setNum(parklot0.total);
    ui->lcdempty->display(parklot0.empty);
    ui->lcdbook->display(parklot0.book);
    ui->lcdleft->display(parklot0.empty-parklot0.book);

    level=parklot0.level;
    feebig=parklot0.feebig;
    feesmall=parklot0.feesmall;
    total=parklot0.total;
    empty=parklot0.empty;
    book=parklot0.book;
}

void MainWindow::receiveData()
{
    refresh();
    std::cout<<"received"<<std::endl;
}
