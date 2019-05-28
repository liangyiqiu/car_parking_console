#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "QMessageBox"

loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_pbtlogin_clicked()
{
    if (ui->lineEditUID->text() == "username" && ui->lineEditPWD->text() == "123456")
    {
        MainWindow *win = new MainWindow;
        win->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Cancel);
        ui->lineEditUID->clear();
        ui->lineEditPWD->clear();
        ui->lineEditUID->setFocus();
    }

}
