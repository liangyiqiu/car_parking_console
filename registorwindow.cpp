#include "registorwindow.h"
#include "loginwindow.h"
#include "ui_registorwindow.h"
#include <fstream>
#include <iostream>
#include <string>
#include "qmessagebox.h"

using namespace std;

registorWindow::registorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registorWindow)
{
    ui->setupUi(this);
}

registorWindow::~registorWindow()
{
    delete ui;
}

void registorWindow::on_pbtregistor_clicked()
{
    if(ui->editPWD->text()==ui->editPWDD->text())
    {
        class usergroup usergroup0[100];
        fstream inFile("user.dat", ios::binary | ios::in);  //以二进制读模式打开文件
        if (!inFile) {
            cout << "Source file open error." << endl;

            for(int i=0;i<100;i++)
            {
                usergroup0[i].status=0;
            }

            fstream outFile("user.dat", ios::out | ios::binary);
            outFile.write((char*)usergroup0, sizeof(usergroup0));
            outFile.close();
            cout<<"initsuccess"<<endl;
        }
        else
        {
            while(inFile.read((char *)usergroup0, sizeof(usergroup0))); //一直读到文件结束
            inFile.close();
        }

        for(int i=0;i<100;i++)
        {
            if(usergroup0[i].status==0)
            {
                usergroup0[i].status=1;
                QString readstr;
                QByteArray readarray;
                char* array;
                readstr=ui->editUID->text();
                readarray=readstr.toLatin1();
                array=readarray.data();
                memcpy(usergroup0[i].username,array,20);

                readstr=ui->editPWD->text();
                readarray=readstr.toLatin1();
                array=readarray.data();
                memcpy(usergroup0[i].passwd,array,20);

                fstream outFile("user.dat", ios::out | ios::binary);
                outFile.write((char*)usergroup0, sizeof(usergroup0));
                outFile.close();

                QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("成功！"),QMessageBox::Cancel);
                cout<<"user number= "<<i<<endl;

                this->close();
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("两次密码输入不一致！"),QMessageBox::Cancel);
        ui->editPWD->clear();
        ui->editPWDD->clear();
    }
}
