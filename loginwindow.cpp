#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "qstylefactory.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qpainter.h"
#include "qpalette.h"

using namespace std;

loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::paintEvent(QPaintEvent *e)
 {
         QPainter p(this );
         //p.fillRect(rect(), QColor(0,0xff,0,30));
         QPixmap pixmap = QPixmap(":/image/beijing3.png").scaled(this->size());
         QPainter painter(this);
         painter.drawPixmap(this->rect(), pixmap);
 }

void loginWindow::on_pbtlogin_clicked()
{    
    if (ui->lineEditUID->text() == "root" && ui->lineEditPWD->text() == "123456")
    {
        MainWindow *win = new MainWindow;
        win->show();
        this->hide();
    }
    else
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

        QString readuid,readpwd;
        QByteArray readarrayuid,readarraypwd;
        char* arrayuid,*arraypwd;
        char uid[20],pwd[50];
        readuid=ui->lineEditUID->text();
        readarrayuid=readuid.toLatin1();
        arrayuid=readarrayuid.data();
        memcpy(uid,arrayuid,20);

        readpwd=ui->lineEditPWD->text();
        readarraypwd=readpwd.toLatin1();
        arraypwd=readarraypwd.data();
        memcpy(pwd,arraypwd,50);

        int i;//counter
        for(i=0;i<100;i++)
        {
            if(strcmp(usergroup0[i].username,uid)==0&&strcmp(usergroup0[i].passwd,pwd)==0
                    &&strlen(uid)!=0
                    )
            {
                cout<<"user number= "<<i<<endl;
                MainWindow *win=new MainWindow;
                win->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
                win->show();
                this->hide();
                break;
            }
        }
        if(i==100)
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Cancel);
            ui->lineEditUID->clear();
            ui->lineEditPWD->clear();
            ui->lineEditUID->setFocus();

        }
    }
}

void loginWindow::on_pbtmin_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}
