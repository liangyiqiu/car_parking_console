#ifndef PKINFOWINDOW_H
#define PKINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class pkinfoWindow;
}

class pkinfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit pkinfoWindow(QWidget *parent = nullptr);
    ~pkinfoWindow();

private slots:
    void on_pbtaccept_clicked();

private:
    Ui::pkinfoWindow *ui;
};

#endif // PKINFOWINDOW_H
