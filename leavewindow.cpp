#include "leavewindow.h"
#include "takewindow.h"
#include "parkwindow.h"
#include "mainwindow.h"
#include "ui_leavewindow.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
    switch (ptr->bigsmall) {
    case 0:ui->lbbigsmall->setText(QString::fromLocal8Bit("大型"));break;
    default:ui->lbbigsmall->setText(QString::fromLocal8Bit("小型"));
    }
}

leaveWindow::~leaveWindow()
{
    delete ui;
}

void leaveWindow::on_pbtleave_clicked()
{
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

    takeWindow *ptr=(takeWindow*)parentWidget();
    carspot0[ptr->number].status=0;

    fstream outFile("spots.dat", ios::out | ios::binary);
    outFile.write((char*)carspot0, sizeof(carspot0));
    outFile.close();


    class parklot parklot0;
    fstream inFile1("parklot.dat", ios::binary | ios::in);  //以二进制读模式打开文件
    if (!inFile1) {
        cout << "Source file open error." << endl;
    }
    else
    {
        while(inFile1.read((char *)&parklot0, sizeof(parklot0))); //一直读到文件结束
        inFile1.close();
    }
    parklot0.empty+=1;


    fstream outFile1("parklot.dat", ios::out | ios::binary);
    outFile1.write((char*)&parklot0, sizeof(parklot0));
    outFile1.close();


    emit sendData();
    this->close();
}
