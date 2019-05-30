#include "takewindow.h"
#include "mainwindow.h"
#include "leavewindow.h"
#include "ui_takewindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qmessagebox.h"
#include "QTime"
#include <ctime>

using namespace std;

takeWindow::takeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::takeWindow)
{
    ui->setupUi(this);
}

takeWindow::~takeWindow()
{
    delete ui;
}

void takeWindow::on_pbtsearch_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();

    class spot carspot0[2000];
    fstream inFile("spots.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile) {
        cout << "Source file open error." << endl;
    }
    else
    {
        while(inFile.read((char *)carspot0, sizeof(carspot0))); //一直读到文件结束
        inFile.close();
    }

    class parklot parklot0;
    ifstream inFile1("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile1) {
        cout << "Source file open error." << endl;
    }
    else
    {
        while(inFile1.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
        inFile1.close();
    }

    switch (ui->cbway->currentIndex())
    {
    case 0:
    {
        QString inputstr=ui->editinput->text();
        number=inputstr.toInt();
        if(carspot0[number].status==1)
        {

            time_t now = time(0);// 基于当前系统的当前日期/时间
            tm* ltm = localtime(&now);
            code=QString::fromLocal8Bit(carspot0[number].code);
            intimehour=carspot0[number].timehour;
            intimemin=carspot0[number].timemin;
            intimedate=carspot0[number].timedate;
            QTime currenttime= QTime::currentTime();
            outtimehour=currenttime.hour();
            outtimemin=currenttime.minute();
            outtimedate = ltm->tm_yday;//取出的日子是今年的第几天
            int lasttime;
            lasttime=(outtimedate-intimedate)*24*60+(outtimehour-intimehour)*60+outtimemin-intimemin;
            timelasthour=lasttime/60;
            timelastmin=lasttime%60;
            bigsmall=carspot0[number].bigsmall;
            feebig=parklot0.feebig;
            feesmall=parklot0.feesmall;

            if(bigsmall==0){
                if(timelastmin<=30){
                    fee=feebig*timelasthour+0.5*feebig;
                }
                else {
                    fee=feebig*(timelasthour+1.0);
                }
            }
            else {
                if(timelastmin<=30){
                    fee=feesmall*timelasthour+0.5*feebig;
                }
                else {
                    fee=feesmall*(timelasthour+1.0);
                }
            }


            leaveWindow *leavewin=new leaveWindow(this);
            connect(leavewin,SIGNAL(sendData()),this,SLOT(receiveData()));
            leavewin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
            leavewin->show();
        }
        else
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("车位是空的！"),QMessageBox::Cancel);
        }
        ui->editinput->clear();
        break;
    }
    case 1:
    {
        int i;//counter
        for(i=0;i<ptr->total;i++)
        {
            if(carspot0[i].status==1)
            {
                QString showstr=QString(QLatin1String(carspot0[i].code));
                if(showstr==ui->editinput->text())
                {
                    number=i;
                    time_t now = time(0);// 基于当前系统的当前日期/时间
                    tm* ltm = localtime(&now);
                    code=QString::fromLocal8Bit(carspot0[i].code);
                    intimehour=carspot0[i].timehour;
                    intimemin=carspot0[i].timemin;
                    intimedate=carspot0[number].timedate;
                    QTime currenttime= QTime::currentTime();
                    outtimehour=currenttime.hour();
                    outtimemin=currenttime.minute();
                    outtimedate = ltm->tm_yday;//取出的日子是今年的第几天
                    int lasttime;
                    lasttime=(outtimedate-intimedate)*24*60+(outtimehour-intimehour)*60+outtimemin-intimemin;
                    timelasthour=lasttime/60;
                    timelastmin=lasttime%60;
                    bigsmall=carspot0[i].bigsmall;
                    feebig=parklot0.feebig;
                    feesmall=parklot0.feesmall;

                    if(bigsmall==0){
                        if(timelastmin<=30){
                            fee=feebig*(timelasthour)+0.5*feebig;
                        }
                        else {
                            fee=feebig*(timelasthour+1.0);
                        }
                    }
                    else {
                        if(timelastmin<=30){
                            fee=feesmall*(timelasthour)+0.5*feebig;
                        }
                        else {
                            fee=feesmall*(timelasthour+1.0);
                        }
                    }

                    leaveWindow *leavewin=new leaveWindow(this);
                    connect(leavewin,SIGNAL(sendData()),this,SLOT(receiveData()));
                    leavewin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
                    leavewin->show();
                    break;
                }
            }
        }
        if(i==ptr->total)
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("该车不在库内！"),QMessageBox::Cancel);
        }
        ui->editinput->clear();
        break;
    }
    }
}

void takeWindow::receiveData()
{
    emit sendData();
}
