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

private:
    Ui::bookWindow *ui;
};

#endif // BOOKWINDOW_H
