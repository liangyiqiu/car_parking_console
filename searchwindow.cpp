#include "searchwindow.h"
#include "parkwindow.h"
#include "mainwindow.h"
#include "ui_searchwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qmessagebox.h"

using namespace std;

searchWindow::searchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchWindow)
{
    ui->setupUi(this);
}

searchWindow::~searchWindow()
{
    delete ui;
}

void searchWindow::on_pbtsearch_clicked()
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
        int number=inputstr.toInt();
        if(carspot0[number].status==1)
        {
            ui->lbnumber->setNum(carspot0[number].number);
            ui->lbname->setText(QString::fromLocal8Bit(carspot0[number].name));
            ui->lbcode->setText(QString::fromLocal8Bit(carspot0[number].code));
            ui->lbphone->setText(QString::fromLocal8Bit(carspot0[number].phone));
            ui->lbtimehour->setNum(carspot0[number].timehour);
            ui->lbtimemin->setNum(carspot0[number].timemin);
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
                    ui->lbnumber->setNum(carspot0[i].number);
                    ui->lbname->setText(QString::fromLocal8Bit(carspot0[i].name));
                    ui->lbcode->setText(QString::fromLocal8Bit(carspot0[i].code));
                    ui->lbphone->setText(QString::fromLocal8Bit(carspot0[i].phone));
                    ui->lbtimehour->setNum(carspot0[i].timehour);
                    ui->lbtimemin->setNum(carspot0[i].timemin);
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


//    for(int i=0;i<ptr->total;i++)
//    {
//        if(carspot0[i].status==1)
//        {

//            carspot0[i].status=1;
//            QString readstr=ui->editcode->text();
//            QByteArray readarray=readstr.toLatin1();
//            char* array=readarray.data();
//            memcpy(carspot0[i].code,array,20);
//            code=ui->editcode->text();

//            readstr=ui->editname->text();
//            readarray=readstr.toLatin1();
//            array=readarray.data();
//            memcpy(carspot0[i].name,array,20);
//            name=ui->editname->text();

//            readstr=ui->editphone->text();
//            carspot0[i].phone=readstr.toInt();
//            phone=readstr.toInt();
//            carspot0[i].bigsmall=ui->cbbigsmall->currentIndex();
//            bigsmall=ui->cbbigsmall->currentIndex();
//            QTime currenttime= QTime::currentTime();
//            carspot0[i].timemin=currenttime.minute();
//            timemin=currenttime.minute();
//            carspot0[i].timehour=currenttime.hour();
//            timehour=currenttime.hour();
//            number=i;

//            fstream outFile("spots.dat", ios::out | ios::binary);
//            outFile.write((char*)carspot0, sizeof(carspot0));
//            outFile.close();

//            class parklot parklot0;
//            fstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
//            if (!inFile) {
//                cout << "Source file open error." << endl;
//            }
//            else
//            {
//                while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
//                inFile.close();
//            }
//            parklot0.empty-=1;


//            fstream outFile1("parklot.dat", ios::out | ios::binary);
//            outFile1.write((char*)&parklot0, sizeof(parklot0));
//            outFile1.close();

//            pkinfoWindow *pkinwin=new pkinfoWindow(this);
//            pkinwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
//            pkinwin->show();

//            ui->editcode->clear();
//            ui->editname->clear();
//            ui->editphone->clear();

//            break;
//        }
//    }
//    emit sendData();
}
