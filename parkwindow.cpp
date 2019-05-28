#include "parkwindow.h"
#include "qtime"
#include "ui_parkwindow.h"


parkWindow::parkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::parkWindow)
{
    ui->setupUi(this);
}

parkWindow::~parkWindow()
{
    delete ui;
}

void parkWindow::on_pbtaccept_clicked()
{
    class spot carspot;
    QTime currenttime= QTime::currentTime();
    QString readstr;
    carspot.timehour=currenttime.hour();
    carspot.timemin=currenttime.minute();
    carspot.status=1;
    carspot.code=ui->editcode->text();
    carspot.name=ui->editname->text();
    readstr=ui->editphone->text();
    carspot.phone=readstr.toInt();
    carspot.bigsmall=ui->cbbigsmall->currentIndex();

}
