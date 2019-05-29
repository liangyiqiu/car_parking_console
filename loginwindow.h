#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class loginWindow;
}

class loginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = nullptr);
    ~loginWindow();

private:
    Ui::loginWindow *ui;
private slots:
    void on_pbtlogin_clicked(void);
};

class usergroup{
public:
    int status=0;
    char username[20];
    char passwd[50];
};

#endif // LOGINWINDOW_H
