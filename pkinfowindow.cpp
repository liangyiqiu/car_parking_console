#include "pkinfowindow.h"
#include "parkwindow.h"
#include "ui_pkinfowindow.h"

//该窗口用于显示刚停入的车辆信息

pkinfoWindow::pkinfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pkinfoWindow)
{
    ui->setupUi(this);
    parkWindow *ptr = (parkWindow*)parentWidget();
    switch (ptr->bigsmall) {
    case 0:ui->lblevel->setText(QString::fromLocal8Bit("大型"));break;
    default:ui->lblevel->setText(QString::fromLocal8Bit("小型"));
    }
    ui->lbnumber->setNum(ptr->number);
    ui->lbcode->setText(ptr->code);
    ui->lbname->setText(ptr->name);
    ui->lbtimehour->setNum(ptr->timehour);
    ui->lbtimemin->setNum(ptr->timemin);
}

pkinfoWindow::~pkinfoWindow()
{
    delete ui;
}

void pkinfoWindow::on_pbtaccept_clicked()
{

    this->close();
}
