#include "usereditwindow.h"
#include "ui_usereditwindow.h"

usereditWindow::usereditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::usereditWindow)
{
    ui->setupUi(this);
}

usereditWindow::~usereditWindow()
{
    delete ui;
}
