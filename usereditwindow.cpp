#include "usereditwindow.h"
#include "ui_usereditwindow.h"

//该窗口用于用户管理，但是我们还没有做（= =）

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
