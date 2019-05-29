#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>

namespace Ui {
class setWindow;
}

class Sdata{
public:
    int level=0;
    float feebig=0;
    float feesmall=0;
    int total=0;
    int book=0;
    int empty=0;
};

class setWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit setWindow(QWidget *parent = nullptr);
    ~setWindow();

private slots:
    void on_pushButton_clicked();

    void on_cblevel_currentIndexChanged(int index);

private:
    Ui::setWindow *ui;

signals:
    void sendData();
};

#endif // SETWINDOW_H
