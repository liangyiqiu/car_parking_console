#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QMainWindow>

namespace Ui {
class initWindow;
}

class initWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit initWindow(QWidget *parent = nullptr);
    ~initWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::initWindow *ui;
};

#endif // INITWINDOW_H
