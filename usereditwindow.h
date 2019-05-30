#ifndef USEREDITWINDOW_H
#define USEREDITWINDOW_H

#include <QMainWindow>

namespace Ui {
class usereditWindow;
}

class usereditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit usereditWindow(QWidget *parent = nullptr);
    ~usereditWindow();

private:
    Ui::usereditWindow *ui;
};

#endif // USEREDITWINDOW_H
