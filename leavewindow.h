#ifndef LEAVEWINDOW_H
#define LEAVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class leaveWindow;
}

class leaveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit leaveWindow(QWidget *parent = nullptr);
    ~leaveWindow();

private:
    Ui::leaveWindow *ui;
};

#endif // LEAVEWINDOW_H
