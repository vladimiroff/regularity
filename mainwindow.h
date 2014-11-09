#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "factory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Factory* GetFactory();

private:
    Ui::MainWindow *ui;
    Factory* factory;

private slots:
    void toggleMainViews();
    void onMoneyChanged(int);
    void onOrderRemoved(int);
    void onOrderCreated(int);
    void onOrderTaken();
};

#endif // MAINWINDOW_H
