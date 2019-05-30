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
    connect(ui->actionlogout,SIGNAL(triggered()),this,SLOT(on_pbtlogout_clicked()));//连接注销事件信号
    connect(ui->actionregister,SIGNAL(triggered()),this,SLOT(fun_register()));//连接注册事件信号
    connect(ui->actionabout,SIGNAL(triggered()),this,SLOT(fun_about()));//连接关于事件信号
    connect(ui->actioninit,SIGNAL(triggered()),this,SLOT(fun_init()));//连接初始化停车场事件信号
    connect(ui->actionpk,SIGNAL(triggered()),this,SLOT(fun_useredit()));//连接修改用户名密码事件信号
    refresh();//刷新主窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbtlogout_clicked()//注销
{
    loginWindow *win = new loginWindow;//创建新的登录窗口
    win->show();
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    this->close();
}



void MainWindow::on_pbtset_clicked()//设置按钮被按下
{
    setWindow *setWin=new setWindow(this);//创建设置窗口
    connect(setWin,SIGNAL(sendData()),this,SLOT(receiveData()));//连接子窗口的信号
    setWin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    setWin->show();
}


void MainWindow::on_pbtpark_clicked()//泊车按钮被按下
{
    parkWindow *parkwin=new parkWindow(this);//创建泊车窗口
    connect(parkwin,SIGNAL(sendData()),this,SLOT(receiveData()));//连接子窗口的信号
    parkwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    parkwin->show();
}

void MainWindow::on_pbtleave_clicked()//取车按钮被按下
{
    takeWindow *takewin = new takeWindow(this);//创建取车窗口
    connect(takewin,SIGNAL(sendData()),this,SLOT(receiveData()));//连接子窗口的信号
    takewin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    takewin->show();
}

void MainWindow::on_pbtsearch_clicked()//查找按钮被按下
{
    searchWindow *searchwin = new searchWindow(this);//创建查找按钮
    searchwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    searchwin->show();
}

void MainWindow::on_pbtbook_clicked()//预定按钮被按下
{
    bookWindow *bookwin=new bookWindow(this);//创建预定窗口
    connect(bookwin,SIGNAL(sendData()),this,SLOT(receiveData()));//连接子窗口的信号
    bookwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    bookwin->show();
}

void MainWindow::refresh()//刷新主窗口内容
{
    class parklot parklot0;//创建停车场信息的实例
    ifstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开存储停车场信息的文件
    if (!inFile) {
        cout << "Source file open error." << endl;
        //如果打开失败则初始化一个新的带有默认数据的文件
        parklot0.book=0;
        parklot0.empty=0;
        parklot0.level=0;
        parklot0.total=0;
        parklot0.feebig=0;
        parklot0.feesmall=0;
        fstream outFile("parklot.dat", ios::out | ios::binary);//写入新的带有默认数据的文件
        outFile.write((char*)&parklot0, sizeof(parklot0));
        outFile.close();
    }
    else
    {
        while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
        inFile.close();
    }

    switch (parklot0.level) {//显示停车场等级
    case 0:ui->lblevel->setText(QString::fromLocal8Bit("核心"));break;
    case 1:ui->lblevel->setText(QString::fromLocal8Bit("一级"));break;
    case 2:ui->lblevel->setText(QString::fromLocal8Bit("二级"));break;
    default:ui->lblevel->setText(QString::fromLocal8Bit("三级"));
    }
    //显示停车场所有信息
    ui->lbfeebig->setNum((double)parklot0.feebig);
    ui->lbfeesmall->setNum((double)parklot0.feesmall);
    ui->lbtotal->setNum(parklot0.total);
    ui->lcdempty->display(parklot0.empty);
    ui->lcdbook->display(parklot0.book);
    ui->lcdleft->display(parklot0.empty-parklot0.book);
    //将停车场信息保存给主窗口
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

void MainWindow::fun_register()//创建注册窗口
{
    registorWindow *rgtwin=new registorWindow(this);
    rgtwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    rgtwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    rgtwin->show();
}

void MainWindow::fun_about()//显示关于信息
{
    QMessageBox::about(this,QString::fromLocal8Bit("关于"),QString::fromLocal8Bit("开发者：梁逸秋 贾睿\n我们的github链接:\nhttps://github.com/liangyiqiu/car_parking_console"));
}

void MainWindow::fun_init()//创建初始化停车场窗口
{
    initWindow *initwin=new initWindow(this);
    initwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    initwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    initwin->show();
}

void MainWindow::fun_useredit()//创建修改用户密码窗口
{
    usereditWindow *ueditwin=new usereditWindow(this);
    ueditwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
    ueditwin->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    ueditwin->show();
}

