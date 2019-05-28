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

private slots:
    void on_pbtaccept_clicked();

private:
    Ui::parkWindow *ui;
};

class  spot{
public:
    int status=0;
    int timehour=0;
    int timemin=0;
    int bigsmall=0;
    QString code;
    QString name;
    int phone=0;
};
extern spot spot[100];

#endif // PARKWINDOW_H
