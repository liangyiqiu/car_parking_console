#include "searchwindow.h"
#include "parkwindow.h"
#include "mainwindow.h"
#include "ui_searchwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "qmessagebox.h"

using namespace std;

searchWindow::searchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchWindow)
{
    ui->setupUi(this);
}

searchWindow::~searchWindow()
{
    delete ui;
}

void searchWindow::on_pbtsearch_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();

    class spot carspot0[2000];
    fstream inFile("spots.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile) {
        cout << "Source file open error." << endl;
    }
    else
    {
        while(inFile.read((char *)carspot0, sizeof(carspot0))); //一直读到文件结束
        inFile.close();
    }

    switch (ui->cbway->currentIndex())//选择查询方式
    {
    case 0://车位号
    {
        QString inputstr=ui->editinput->text();
        int number=inputstr.toInt();
        if(carspot0[number].status==1)
        {
            ui->lbnumber->setNum(carspot0[number].number);
            ui->lbname->setText(QString::fromLocal8Bit(carspot0[number].name));
            ui->lbcode->setText(QString::fromLocal8Bit(carspot0[number].code));
            ui->lbphone->setText(QString::fromLocal8Bit(carspot0[number].phone));
            ui->lbtimehour->setNum(carspot0[number].timehour);
            ui->lbtimemin->setNum(carspot0[number].timemin);
            switch (carspot0[number].bigsmall) {
            case 0:ui->lbbigsmall->setText(QString::fromLocal8Bit("大型"));break;
            default:ui->lbbigsmall->setText(QString::fromLocal8Bit("小型"));
            }
        }
        else
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("车位是空的！"),QMessageBox::Cancel);
        }
        ui->editinput->clear();
        break;
    }
    case 1://车牌号
    {
        int i;//counter
        for(i=0;i<ptr->total;i++)
        {
            if(carspot0[i].status==1)
            {
                QString showstr=QString(QLatin1String(carspot0[i].code));
                if(showstr==ui->editinput->text())
                {
                    ui->lbnumber->setNum(carspot0[i].number);
                    ui->lbname->setText(QString::fromLocal8Bit(carspot0[i].name));
                    ui->lbcode->setText(QString::fromLocal8Bit(carspot0[i].code));
                    ui->lbphone->setText(QString::fromLocal8Bit(carspot0[i].phone));
                    ui->lbtimehour->setNum(carspot0[i].timehour);
                    ui->lbtimemin->setNum(carspot0[i].timemin);
                    switch (carspot0[i].bigsmall) {
                    case 0:ui->lbbigsmall->setText(QString::fromLocal8Bit("大型"));break;
                    default:ui->lbbigsmall->setText(QString::fromLocal8Bit("小型"));
                    }
                    break;
                }
            }
        }
        if(i==ptr->total)
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("该车不在库内！"),QMessageBox::Cancel);
        }
        ui->editinput->clear();
        break;
    }
    }

}
