#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setwindow.h"
#include "parkwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtlogout_clicked();

    void on_pbtset_clicked();

    void receiveData();//接收子窗口信号的槽函数

    void fun_register();//创建注册页面的函数

    void fun_about();//显示关于信息的函数

    void fun_init();//创建初始化停车场页面的函数

    void fun_useredit();//创建修改用户名密码页面的函数

    void on_pbtpark_clicked();

    void on_pbtleave_clicked();

    void on_pbtsearch_clicked();

    void on_pbtbook_clicked();

private:
    Ui::MainWindow *ui;

public:
    //创建以下变量用于显示和子窗口调用
    int level=0;//停车场等级
    float feebig=0;//大车收费
    float feesmall=0;//小车收费
    int total=0;//总停车位数量
    int book=0;//预定车位数量
    int empty=0;//空车位数量
public:
    void refresh(void);//刷新主窗口内容
};

class parklot{//关于停车场信息的类
public:
    int level;
    float feebig;
    float feesmall;
    int total=0;
    int book=0;
    int empty=0;
};

#endif // MAINWINDOW_H
