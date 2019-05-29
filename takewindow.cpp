#include "takewindow.h"
#include "mainwindow.h"
#include "leavewindow.h"
#include "ui_takewindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qmessagebox.h"
#include "QTime"

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

    switch (ui->cbway->currentIndex())
    {
    case 0:
    {
        QString inputstr=ui->editinput->text();
        number=inputstr.toInt();
        if(carspot0[number].status==1)
        {
            code=QString::fromLocal8Bit(carspot0[number].code);
            intimehour=carspot0[number].timehour;
            intimemin=carspot0[number].timemin;
            QTime currenttime= QTime::currentTime();
            outtimehour=currenttime.hour();
            outtimemin=currenttime.minute();
            int lasttime;
            lasttime=(outtimehour-intimehour)*60+outtimemin-intimemin;
            timelasthour=lasttime/60;
            timelastmin=lasttime%60;
            fee=0.6*lasttime;

            leaveWindow *leavewin=new leaveWindow(this);
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
                    code=QString::fromLocal8Bit(carspot0[i].code);
                    intimehour=carspot0[i].timehour;
                    intimemin=carspot0[i].timemin;
                    QTime currenttime= QTime::currentTime();
                    outtimehour=currenttime.hour();
                    outtimemin=currenttime.minute();
                    int lasttime;
                    lasttime=(outtimehour-intimehour)*60+outtimemin-intimemin;
                    timelasthour=lasttime/60;
                    timelastmin=lasttime%60;
                    fee=0.6*lasttime;

                    leaveWindow *leavewin=new leaveWindow(this);
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
