#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "factory.h"
#include "storage.h"

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
    void disableInput();
    void enableInput();

private:
    Ui::MainWindow *ui;
    Factory* factory;
    Storage* storage;
    QSignalMapper* signalMapper;
    QSignalMapper* shopSignalMapper;
    Store store;

public slots:
    void onAddedMaterial(std::string);
    void onTookMaterial(QString);
    void onPartBought(QString);

private slots:
    void toggleMainViews();
    void onMoneyChanged(int);
    void onOrderRemoved(int);
    void onOrderCreated(int);
    void onOrderTaken();
    void onCheck();
    void onRatingChanged(float);
    void populateStore();
};

#endif // MAINWINDOW_H
