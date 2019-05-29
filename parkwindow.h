#ifndef PARKWINDOW_H
#define PARKWINDOW_H

#include <QMainWindow>
#include "qstring.h"

namespace Ui {
class parkWindow;
}

class parkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit parkWindow(QWidget *parent = nullptr);
    ~parkWindow();

signals:
    void sendData();

private slots:
    void on_pbtaccept_clicked();

private:
    Ui::parkWindow *ui;

public:
    int total=0;
    int left=0;
    int number=0;
    int status=0;
    int timehour=0;
    int timemin=0;
    int bigsmall=0;
    QString code;
    QString name;
    QString phone;
};

class  spot{
public:
    int number=0;
    int left=0;
    int status=0;
    int timedate=0;
    int timehour=0;
    int timemin=0;
    int bigsmall=0;
    char code[20]={0};
    char name[20]={0};
    char phone[20]={0};
};
extern spot spot[100];

#endif // PARKWINDOW_H
