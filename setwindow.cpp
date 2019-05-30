#include "setwindow.h"
#include "mainwindow.h"
#include "ui_setwindow.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

setWindow::setWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setWindow)
{
    ui->setupUi(this);
    MainWindow *ptr = (MainWindow*)parentWidget();//创建父窗口指针，从父窗口（主窗口）读取数值显示，即显示当前停车场信息
    ui->cblevel->setCurrentIndex(ptr->level);
    std::string showstr=std::to_string((int)ptr->feebig);
    ui->editfeebig->setText(showstr.c_str());
    showstr=std::to_string((int)ptr->feesmall);
    ui->editfeesmall->setText(showstr.c_str());
    showstr=std::to_string(ptr->total);
    ui->edittotal->setText(showstr.c_str());
    showstr=std::to_string(ptr->empty);
    ui->editempty->setText(showstr.c_str());
    showstr=std::to_string(ptr->book);
    ui->editbook->setText(showstr.c_str());
    switch (ptr->level) {
    case 0: ui->lbsgstfeebig->setText("4.5");ui->lbsgstfeesmall->setText("4");break;
    case 1: ui->lbsgstfeebig->setText("3.5");ui->lbsgstfeesmall->setText("3");break;
    case 2: ui->lbsgstfeebig->setText("2");ui->lbsgstfeesmall->setText("1.5");break;
    default: ui->lbsgstfeebig->setText("1.5");ui->lbsgstfeesmall->setText("0.5");
    }
}

setWindow::~setWindow()
{
    delete ui;
}

void setWindow::on_pushButton_clicked()//确认按钮被按下，修改停车场信息
{
    class parklot parklot0;
    QString readstr;
    parklot0.level=ui->cblevel->currentIndex();
    readstr=ui->editfeebig->text();
    parklot0.feebig=readstr.toFloat();
    readstr=ui->editfeesmall->text();
    parklot0.feesmall=readstr.toFloat();
    readstr=ui->edittotal->text();
    parklot0.total=readstr.toInt();
    readstr=ui->editempty->text();
    parklot0.empty=readstr.toInt();
    readstr=ui->editbook->text();
    parklot0.book=readstr.toInt();

    fstream outFile("parklot.dat", ios::out | ios::binary);//写入停车场信息文件
    outFile.write((char*)&parklot0, sizeof(parklot0));
    outFile.close();

    emit sendData();//发送信号，让主窗口刷新
    this->close();
}

void setWindow::on_cblevel_currentIndexChanged(int index)//根据用户在ComBox选择的停车场等级显示建议收费
{
    switch (index) {
    case 0: ui->lbsgstfeebig->setText("4.5");ui->lbsgstfeesmall->setText("4");break;
    case 1: ui->lbsgstfeebig->setText("3.5");ui->lbsgstfeesmall->setText("3");break;
    case 2: ui->lbsgstfeebig->setText("2");ui->lbsgstfeesmall->setText("1.5");break;
    default: ui->lbsgstfeebig->setText("1.5");ui->lbsgstfeesmall->setText("0.5");
    }
}
