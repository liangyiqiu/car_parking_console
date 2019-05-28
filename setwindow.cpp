#include "setwindow.h"
#include "mainwindow.h"
#include "ui_setwindow.h"
#include <iostream>
#include <string>

setWindow::setWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setWindow)
{
    ui->setupUi(this);
    MainWindow *ptr = (MainWindow*)parentWidget();
    ui->cblevel->setCurrentIndex(ptr->level);
    std::string showstr=std::to_string((int)ptr->feebig);
    ui->editfeebig->setText(showstr.c_str());
    showstr=std::to_string((int)ptr->feesmall);
    ui->editfeesmall->setText(showstr.c_str());
    showstr=std::to_string(ptr->total);
    ui->edittotal->setText(showstr.c_str());
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

void setWindow::on_pushButton_clicked()
{
    Sdata data;
    QString readstr;
    data.level=ui->cblevel->currentIndex();
    readstr=ui->editfeebig->text();
    data.feebig=readstr.toFloat();
    readstr=ui->editfeesmall->text();
    data.feesmall=readstr.toFloat();
    readstr=ui->edittotal->text();
    data.total=readstr.toInt();
    emit sendData(data);
    this->hide();
}

void setWindow::on_cblevel_currentIndexChanged(int index)
{
    switch (index) {
    case 0: ui->lbsgstfeebig->setText("4.5");ui->lbsgstfeesmall->setText("4");break;
    case 1: ui->lbsgstfeebig->setText("3.5");ui->lbsgstfeesmall->setText("3");break;
    case 2: ui->lbsgstfeebig->setText("2");ui->lbsgstfeesmall->setText("1.5");break;
    default: ui->lbsgstfeebig->setText("1.5");ui->lbsgstfeesmall->setText("0.5");
    }
}
