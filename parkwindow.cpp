#include "parkwindow.h"
#include "mainwindow.h"
#include "pkinfowindow.h"
#include "QTime"
#include <fstream>
#include <iostream>
#include "ui_parkwindow.h"
#include <ctime>

using namespace std;

parkWindow::parkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::parkWindow)
{
    ui->setupUi(this);
    MainWindow *ptr = (MainWindow*)parentWidget();
    left=ptr->empty-ptr->book;
    total=ptr->total;
}

parkWindow::~parkWindow()
{
    delete ui;
}

void parkWindow::on_pbtaccept_clicked()
{
//#define INIT
#ifdef INIT
    class spot carspot[2000];
    QTime currenttime= QTime::currentTime();
    QString readstr;
    for(int i =0;i<2000;i++)
    {
    carspot[i].timehour=0;//currenttime.hour();
    carspot[i].timemin=0;//currenttime.minute();
    carspot[i].status=0;
//    carspot[0].code://ui->editcode->text();
//    carspot[0].name;//ui->editname->text();
//    //readstr=ui->editphone->text();
//    carspot[i].phone;//readstr.toInt();
    carspot[i].bigsmall=0;//ui->cbbigsmall->currentIndex();
    carspot[i].number=i;
    }
    fstream outFile("spots.dat", ios::out | ios::binary);
    outFile.write((char*)carspot, sizeof(carspot));
    outFile.close();
    cout<<"initsuccess"<<endl;
#endif


    class spot carspot0[2000];
    fstream inFile("spots.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile) {
        cout << "Source file open error." << endl;
        for(int i=0;i<2000;i++)
        {
            carspot0[i].timehour=0;//currenttime.hour();
            carspot0[i].timemin=0;//currenttime.minute();
            carspot0[i].timedate=0;
            carspot0[i].status=0;
            carspot0[i].bigsmall=0;//ui->cbbigsmall->currentIndex();
            carspot0[i].number=i;
        }
    }
    else
    {
        while(inFile.read((char *)carspot0, sizeof(carspot0))); //一直读到文件结束
        inFile.close();
    }

    for(int i=0;i<total;i++)
    {
        if(carspot0[i].status==0)
        {
            time_t now = time(nullptr);// 基于当前系统的当前日期/时间
            tm* ltm = localtime(&now);
            carspot0->timedate=ltm->tm_yday;//停入的日子是今年的第几天

            carspot0[i].status=1;
            QString readstr=ui->editcode->text();
            QByteArray readarray=readstr.toLatin1();
            char* array=readarray.data();
            memcpy(carspot0[i].code,array,20);
            code=ui->editcode->text();

            readstr=ui->editname->text();
            readarray=readstr.toLatin1();
            array=readarray.data();
            memcpy(carspot0[i].name,array,20);
            name=ui->editname->text();

            readstr=ui->editphone->text();
            readarray=readstr.toLatin1();
            array=readarray.data();
            memcpy(carspot0[i].phone,array,20);
            phone=ui->editphone->text();

            carspot0[i].bigsmall=ui->cbbigsmall->currentIndex();
            bigsmall=ui->cbbigsmall->currentIndex();
            QTime currenttime= QTime::currentTime();
            carspot0[i].timemin=currenttime.minute();
            timemin=currenttime.minute();
            carspot0[i].timehour=currenttime.hour();
            timehour=currenttime.hour();
            number=i;

            fstream outFile("spots.dat", ios::out | ios::binary);
            outFile.write((char*)carspot0, sizeof(carspot0));
            outFile.close();

            class parklot parklot0;
            fstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
            if (!inFile) {
                cout << "Source file open error." << endl;
            }
            else
            {
                while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
                inFile.close();
            }
            parklot0.empty-=1;


            fstream outFile1("parklot.dat", ios::out | ios::binary);
            outFile1.write((char*)&parklot0, sizeof(parklot0));
            outFile1.close();

            pkinfoWindow *pkinwin=new pkinfoWindow(this);
            pkinwin->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体之外的所有的窗体
            pkinwin->show();

            ui->editcode->clear();
            ui->editname->clear();
            ui->editphone->clear();

            break;
        }
    }
    emit sendData();
}
