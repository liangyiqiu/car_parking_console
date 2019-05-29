#include "leavewindow.h"
#include "takewindow.h"
#include "ui_leavewindow.h"

leaveWindow::leaveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaveWindow)
{
    ui->setupUi(this);
    takeWindow *ptr = (takeWindow*)parentWidget();
    ui->lcdfee->display(ptr->fee);
    ui->lbcode->setText(ptr->code);
    ui->lbnumer->setNum(ptr->number);
    ui->lbintimehour->setNum(ptr->intimehour);
    ui->lbintimemin->setNum(ptr->intimemin);
    ui->lbouttimehour->setNum(ptr->outtimehour);
    ui->lbouttimemin->setNum(ptr->outtimemin);
    ui->lbtimelasthour->setNum(ptr->timelasthour);
    ui->lbtimelastmin->setNum(ptr->timelastmin);
}

leaveWindow::~leaveWindow()
{
    delete ui;
}
