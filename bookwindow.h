#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class bookWindow;
}

class bookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit bookWindow(QWidget *parent = nullptr);
    ~bookWindow();

private slots:
    void on_spbhour_valueChanged(int arg1);

private slots:
    void on_pbtbook_clicked();

    void on_pbtexit_clicked();

private:
    Ui::bookWindow *ui;


signals:
    void sendData();

public:
    int timecheckflag=0;//用于第一次初始化时间时不提示时间不正确；
};

class bookspot{
public:
    int number=0;
    int timemin=0;
    int timehour=0;
    char code[20]={0};
};

class blacklist{
public:
    int number=0;
    char code[20]={0};
};

#endif // BOOKWINDOW_H

