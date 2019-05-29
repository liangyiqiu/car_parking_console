#ifndef TAKEWINDOW_H
#define TAKEWINDOW_H

#include <QMainWindow>

namespace Ui {
class takeWindow;
}

class takeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit takeWindow(QWidget *parent = nullptr);
    ~takeWindow();

private slots:
    void on_pbtsearch_clicked();
    void receiveData();

signals:
    void sendData();

private:
    Ui::takeWindow *ui;

public:
    QString code;
    int number;
    int intimehour;
    int intimemin;
    int intimedate;
    int outtimehour;
    int outtimemin;
    int outtimedate;
    int timelasthour;
    int timelastmin;
    int fee;
    int bigsmall;
    float feebig;
    float feesmall;
};

#endif // TAKEWINDOW_H
