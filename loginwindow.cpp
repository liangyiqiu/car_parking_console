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
         QPixmap pixmap = QPixmap(":/image/beijing3.png").scaled(this->size());//设置背景图片
         QPainter painter(this);
         painter.drawPixmap(this->rect(), pixmap);
 }

void loginWindow::on_pbtlogin_clicked()//登录键被按下
{    
    if (ui->lineEditUID->text() == "root" && ui->lineEditPWD->text() == "123456")//写入程序的管理员密码，防止用户数据文件丢失无法登录
    {
        MainWindow *win = new MainWindow;
        win->show();
        this->close();
    }
    else
    {
        class usergroup usergroup0[100];//读取用户数据文件
        fstream inFile("user.dat", ios::binary | ios::in);  //以二进制读模式打开文件
        if (!inFile) {
            cout << "Source file open error." << endl;
            for(int i=0;i<100;i++)//打开失败则写入空白用户文件
            {
                usergroup0[i].status=0;//使每个用户实例状态为未注册
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

        QString readuid,readpwd;//创建一些字符串用于转化用户输入的用户名和密码的数据格式
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
            if(strcmp(usergroup0[i].username,uid)==0&&strcmp(usergroup0[i].passwd,pwd)==0//比较用户名和密码
                    &&strlen(uid)!=0//用户名和密码不能为空
                    )
            {
                cout<<"user number= "<<i<<endl;
                MainWindow *win=new MainWindow;//创建主页面
                win->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
                win->show();
                this->close();
                break;
            }
        }
        if(i==100)
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Cancel);
            ui->lineEditUID->clear();//清空输入
            ui->lineEditPWD->clear();
            ui->lineEditUID->setFocus();

        }
    }
}

void loginWindow::on_pbtmin_clicked()//最小化按钮被按下
{
    this->setWindowState(Qt::WindowMinimized);//最小化窗口
}
