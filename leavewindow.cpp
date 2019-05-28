#include "leavewindow.h"
#include "ui_leavewindow.h"

leaveWindow::leaveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaveWindow)
{
    ui->setupUi(this);
}

leaveWindow::~leaveWindow()
{
    delete ui;
}
