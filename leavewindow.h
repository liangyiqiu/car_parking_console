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

private slots:
    void on_pbtleave_clicked();

private:
    Ui::leaveWindow *ui;

signals:
    void sendData();
};

#endif // LEAVEWINDOW_H
