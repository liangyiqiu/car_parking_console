#ifndef REGISTORWINDOW_H
#define REGISTORWINDOW_H

#include <QMainWindow>

namespace Ui {
class registorWindow;
}

class registorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registorWindow(QWidget *parent = nullptr);
    ~registorWindow();

private slots:
    void on_pbtregistor_clicked();

private:
    Ui::registorWindow *ui;
};

#endif // REGISTORWINDOW_H
