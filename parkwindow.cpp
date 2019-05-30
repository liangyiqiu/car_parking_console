#include "parkwindow.h"
#include "mainwindow.h"
#include "bookwindow.h"
#include "pkinfowindow.h"
#include "QTime"
#include <fstream>
#include <iostream>
#include "ui_parkwindow.h"
#include <ctime>
#include <string>
#include "qmessagebox.h"

using namespace std;

parkWindow::parkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::parkWindow)
{
    ui->setupUi(this);
    MainWindow *ptr = (MainWindow*)parentWidget();//创建父窗口指针
    left=ptr->empty-ptr->book;//读取剩余车位数
    total=ptr->total;
}

parkWindow::~parkWindow()
{
    delete ui;
}

void parkWindow::on_pbtaccept_clicked()
{
    if(left>0)
    {
        class spot carspot0[2000];
        fstream inFile("spots.dat", ios::binary | ios::in);  //以二进制读模式打开文件
        if (!inFile) {
            cout << "Source file open error." << endl;
            for(int i=0;i<2000;i++)//如果失败，写入新数据文件
            {
                carspot0[i].timehour=0;
                carspot0[i].timemin=0;
                carspot0[i].timedate=0;
                carspot0[i].status=0;
                carspot0[i].bigsmall=0;
                carspot0[i].number=i;

            }
            fstream outFile("spots.dat", ios::out | ios::binary);
            outFile.write((char*)carspot0, sizeof(carspot0));
            outFile.close();
            cout<<"initsuccess"<<endl;
        }
        else
        {
            while(inFile.read((char *)carspot0, sizeof(carspot0))); //一直读到文件结束
            inFile.close();
        }

        for(int i=0;i<total;i++)
        {
            if(carspot0[i].status==0)//判断车位是否为空
            {
                time_t now = time(nullptr);// 基于当前系统的当前日期/时间
                tm* ltm = localtime(&now);
                carspot0[i].timedate=ltm->tm_yday;//停入的日子是今年的第几天

                carspot0[i].status=1;//停入
                //写入车辆信息
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
                number=i;//车位号



                fstream outFile("spots.dat", ios::out | ios::binary);
                outFile.write((char*)carspot0, sizeof(carspot0));
                outFile.close();

                class parklot parklot0;
                fstream inFile("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开停车场信息文件
                if (!inFile) {
                    cout << "Source file open error." << endl;
                }
                else
                {
                    while(inFile.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
                    inFile.close();
                }
                parklot0.empty-=1;//空车位减一

                class bookspot bspot0[2000];
                fstream inFile1("bookspots.dat", ios::binary | ios::in);  //以二进制写模式打开预定信息文件
                if (!inFile1) {
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
                for(int m=0;m<2000;m++)
                {
                    if(code.compare(bspot0[m].code)==0)
                    {
                        if((timehour==bspot0[m].timehour&&timemin>=bspot0[m].timemin)||timehour>=bspot0[m].timehour)
                        {
                            class blacklist blacklist0[2000];
                            fstream inFile2("blacklist.dat", ios::binary | ios::in);  //以二进制读模式打开文件
                            if (!inFile2) {
                                cout << "Source file open error." << endl;
                            }
                            else
                            {
                                while(inFile2.read((char *)&blacklist0, sizeof(blacklist0))); //一直读到文件结束
                                inFile2.close();
                            }
                            for(int j=0;j<2000;j++)
                            {
                                if(code.compare(blacklist0[j].code)==0)//在黑名单信息中比较车牌
                                {
                                    blacklist0[j].number++;//爽约次数加一

                                    fstream outFile0("blacklist.dat", ios::out | ios::binary);
                                    outFile0.write((char*)&blacklist0, sizeof(blacklist0));
                                    outFile0.close();
                                    break;
                                }
                                else {
                                    if(blacklist0[j].number==0)
                                    {
                                        readstr=ui->editcode->text();
                                        readarray=readstr.toLatin1();
                                        char* array=readarray.data();
                                        memcpy(blacklist0[j].code,array,20);
                                        blacklist0[j].number=1;

                                        fstream outFile0("blacklist.dat", ios::out | ios::binary);
                                        outFile0.write((char*)&blacklist0, sizeof(blacklist0));
                                        outFile0.close();
                                        break;
                                    }
                                }
                            }
                        }
                        strcpy( bspot0[i].code, "0");
                        bspot0[i].number=0;
                        bspot0[i].timemin=0;
                        bspot0[i].timehour=0;
                        parklot0.book-=1;
                        break;
                    }
                }


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
        emit sendData();//发送信号刷新主窗口
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("没有剩余车位！"),QMessageBox::Cancel);
    }
}
