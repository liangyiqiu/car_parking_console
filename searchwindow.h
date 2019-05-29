#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class searchWindow;
}

class searchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchWindow(QWidget *parent = nullptr);
    ~searchWindow();

private slots:
    void on_pbtsearch_clicked();

private:
    Ui::searchWindow *ui;
};

#endif // SEARCHWINDOW_H
