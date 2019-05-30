#include "bookwindow.h"
#include "mainwindow.h"
#include "ui_bookwindow.h"
#include "qmessagebox.h"
#include "QTime"
#include<iostream>
#include<fstream>
#include <string>

using namespace std;

bookWindow::bookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookWindow)
{
    ui->setupUi(this);
    QTime currenttime= QTime::currentTime();
    if(currenttime.minute()<30)
    {
        ui->spbhour->setValue(currenttime.hour());
        ui->spbmin->setValue(currenttime.minute()+30);
    }
    else
    {
        ui->spbhour->setValue(currenttime.hour()+1);
        ui->spbmin->setValue(currenttime.minute()-30);
    }
    ui->spbhour->setRange(0,24);
    ui->spbmin->setRange(0,59);
    timecheckflag=1;
}

bookWindow::~bookWindow()
{
    delete ui;
}

void bookWindow::on_spbhour_valueChanged(int arg1)
{
    if(timecheckflag==1)
    {
        QTime currenttime= QTime::currentTime();
        int timediff=(ui->spbhour->value()-currenttime.hour())*60+ui->spbmin->value()-currenttime.minute();
        if(timediff<30)
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过迟"),QMessageBox::Cancel);
        if(timediff>60)
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过早"),QMessageBox::Cancel);
    }
}
void bookWindow::on_pbtbook_clicked()
{
    QTime currenttime= QTime::currentTime();
    int timediff=(ui->spbhour->value()-currenttime.hour())*60+ui->spbmin->value()-currenttime.minute();
    if(timediff<30)
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过迟"),QMessageBox::Cancel);
    if(timediff>60)
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过早"),QMessageBox::Cancel);

    if(timediff>=30&&timediff<=60)
    {
        class parklot parklot0;
        fstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
        if (!inFile) {
            cout << "Source file open error." << endl;
        }
        else
        {
            while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
            inFile.close();
            cout<<"parklot loaded"<<endl;
        }

        cout<<parklot0.empty<<endl;

        class bookspot bspot0[2000];
        fstream inFile1("bookspots.dat", ios::binary | ios::in);  //以二进制写模式打开文件
        if (!inFile1)
        {
            cout << "Source file open error." << endl;
            for(int i=0;i<2000;i++)
            {
                bspot0[i].number=0;
                bspot0[i].timemin=0;
                bspot0[i].timehour=0;
            }
            fstream outFile("bookspots.dat", ios::out | ios::binary);
            outFile.write((char*)bspot0, sizeof(bspot0));
            outFile.close();
        }
        else
        {
            while(inFile1.read((char *)bspot0, sizeof(bspot0))); //一直读到文件结束
            inFile1.close();
        }

        class blacklist blacklist0[2000];
        fstream inFile2("blacklist.dat", ios::binary | ios::in);  //以二进制读模式打开文件
        if (!inFile2) {
            cout << "Source file open error." << endl;
            for(int i;i<2000;i++)
            {
                blacklist0[i].number=0;
            }
            fstream outFile("blacklist.dat", ios::out | ios::binary);
            outFile.write((char*)blacklist0, sizeof(blacklist0));
            outFile.close();
        }
        else
        {
            while(inFile2.read((char *)&blacklist0, sizeof(blacklist0))); //一直读到文件结束
            inFile2.close();
        }

        for(int i=0;i<2000;i++)
        {
            if(bspot0[i].number==0)
            {
                QString readstr=ui->lineEdit->text();
                QByteArray readarray=readstr.toLatin1();
                char* array=readarray.data();
                QString code=ui->lineEdit->text();
                for(int j=0;j<=2000;j++)
                {
                    if((code.compare(blacklist0[j].code)==0)&&blacklist0[j].number==2)
                    {
                        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该车牌号失约次数超限，不能预约"),QMessageBox::Cancel);
                        return;
                    }
                }
                memcpy(bspot0[i].code,array,20);

                bspot0[i].timemin=ui->spbmin->value();
                bspot0[i].timehour=ui->spbhour->value();

                bspot0[i].number=1;

                cout<<i<<endl;

                fstream outFile("bookspots.dat", ios::out | ios::binary);
                outFile.write((char*)bspot0, sizeof(bspot0));
                outFile.close();

                parklot0.book+=1;
                cout<<parklot0.book<<endl;

                fstream outFile1("parklot.dat", ios::out | ios::binary);
                outFile1.write((char*)&parklot0, sizeof(parklot0));
                outFile1.close();
                ui->lineEdit->clear();
            }
            QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("预约成功！"),QMessageBox::Cancel);
            break;
        }

        emit sendData();

    }
    else
    {
        ;
    }
}


void bookWindow::on_pbtexit_clicked()
{
    timecheckflag=0;
    this->close();
}
