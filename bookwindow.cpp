#include "bookwindow.h"
#include "ui_bookwindow.h"
#include "qmessagebox.h"
#include "QTime"

bookWindow::bookWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookWindow)
{
    ui->setupUi(this);
    QTime currenttime= QTime::currentTime();
    ui->spbhour->setValue(currenttime.hour());
    ui->spbhour->setRange(0,24);
    ui->spbmin->setValue(currenttime.minute());
    ui->spbmin->setRange(0,59);
}

bookWindow::~bookWindow()
{
    delete ui;
}

void bookWindow::on_spbhour_valueChanged(int arg1)
{
//    QTime currenttime= QTime::currentTime();
//    int timediff=(ui->spbhour->value()-currenttime.hour())*60+ui->spbmin->value()-currenttime.minute();
//    if(timediff<30)
//        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过迟"),QMessageBox::Cancel);
//    if(timediff>60)
//        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("预约时间过早"),QMessageBox::Cancel);
}
