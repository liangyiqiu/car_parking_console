#include "mainwindow.h"
#include "loginwindow.h"
#include "setwindow.h"
#include "parkwindow.h"
#include "searchwindow.h"
#include "bookwindow.h"
#include "ui_mainwindow.h"
#include "leavewindow.h"
#include "initwindow.h"
#include "takewindow.h"
#include "usereditwindow.h"
#include "registorwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qmessagebox.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionlogout,SIGNAL(triggered()),this,SLOT(on_pbtlogout_clicked()));
    connect(ui->actionregister,SIGNAL(triggered()),this,SLOT(fun_register()));
    connect(ui->actionabout,SIGNAL(triggered()),this,SLOT(fun_about()));
    connect(ui->actioninit,SIGNAL(triggered()),this,SLOT(fun_init()));
    connect(ui->actionpk,SIGNAL(triggered()),this,SLOT(fun_useredit()));
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
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    this->close();
}



void MainWindow::on_pbtset_clicked()
{
    setWindow *setWin=new setWindow(this);
    connect(setWin,SIGNAL(sendData()),this,SLOT(receiveData()));
    setWin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    setWin->show();
}


void MainWindow::on_pbtpark_clicked()
{
    parkWindow *parkwin=new parkWindow(this);
    connect(parkwin,SIGNAL(sendData()),this,SLOT(receiveData()));
    parkwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    parkwin->show();
}

void MainWindow::on_pbtleave_clicked()
{
    takeWindow *takewin = new takeWindow(this);
    connect(takewin,SIGNAL(sendData()),this,SLOT(receiveData()));
    takewin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    takewin->show();
}

void MainWindow::on_pbtsearch_clicked()
{
    searchWindow *searchwin = new searchWindow(this);
    searchwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    searchwin->show();
}

void MainWindow::on_pbtbook_clicked()
{
    bookWindow *bookwin=new bookWindow(this);
    connect(bookwin,SIGNAL(sendData()),this,SLOT(receiveData()));
    bookwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    bookwin->show();
}

void MainWindow::refresh()
{
    class parklot parklot0;
    ifstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile) {
        cout << "Source file open error." << endl;
        parklot0.book=0;
        parklot0.empty=0;
        parklot0.level=0;
        parklot0.total=0;
        parklot0.feebig=0;
        parklot0.feesmall=0;
        fstream outFile("parklot.dat", ios::out | ios::binary);
        outFile.write((char*)&parklot0, sizeof(parklot0));
        outFile.close();
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

    ui->lbfeebig->setNum((double)parklot0.feebig);
    ui->lbfeesmall->setNum((double)parklot0.feesmall);
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

void MainWindow::receiveData()//收到信号，更新主界面
{
    refresh();
    std::cout<<"mainwindow refreshed"<<std::endl;
}

void MainWindow::fun_register()
{
    registorWindow *rgtwin=new registorWindow(this);
    rgtwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    rgtwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    rgtwin->show();
}

void MainWindow::fun_about()
{
    QMessageBox::about(this,QString::fromLocal8Bit("关于"),QString::fromLocal8Bit("开发者：梁逸秋 贾睿\n我们的github链接:\nhttps://github.com/liangyiqiu/car_parking_console"));
}

void MainWindow::fun_init()
{
    initWindow *initwin=new initWindow(this);
    initwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    initwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    initwin->show();
}

void MainWindow::fun_useredit()
{
    usereditWindow *ueditwin=new usereditWindow(this);
    ueditwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    ueditwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    ueditwin->show();
}

