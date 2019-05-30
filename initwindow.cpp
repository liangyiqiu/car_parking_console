#include "initwindow.h"
#include "mainwindow.h"
#include "ui_initwindow.h"
#include<iostream>
#include<cstdio>
#include<qmessagebox.h>

using namespace std;

initWindow::initWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initWindow)
{
    ui->setupUi(this);
}

initWindow::~initWindow()
{
    delete ui;
}

void initWindow::on_pushButton_clicked()
{
    int step=0;
    if(remove("parklot.dat")==0)
    {
        cout<<"parklot.dat removed"<<endl;
        step+=1;
    }
    else
    {
        cout<<"parklot.dat remove failed"<<endl;
    }

    if(remove("spots.dat")==0)
    {
        cout<<"spots.dat removed"<<endl;
        step+=1;
    }
    else
    {
        cout<<"spots.dat remove failed"<<endl;
    }

    if(remove("bookspots.dat")==0)
    {
        cout<<"bookspots.dat removed"<<endl;
        step+=1;
    }
    else
    {
        cout<<"bookspots.dat remove failed"<<endl;
    }

    if(remove("blacklist.dat")==0)
    {
        cout<<"blacklist.dat removed"<<endl;
        step+=1;
    }
    else
    {
        cout<<"blacklist.dat remove failed"<<endl;
    }

    if(step==4)
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("初始化成功！"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("初始化失败！"),QMessageBox::Cancel);
    }
     MainWindow *ptr = (MainWindow*)parentWidget();
     ptr->refresh();
}
