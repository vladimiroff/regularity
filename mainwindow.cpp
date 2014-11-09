#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "factory.h"
#include <map>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::map<std::string,int> storageItems;
    storageItems["\w"] = 5;
    storageItems["[aeoui]"] = 3;
    storageItems[".?"] = 3;
    storageItems["\d"] = 7;

    Storage* storage = new Storage(storageItems);
    Factory* factory = new Factory(storage, 5, 1.2, 5, 2, 1, std::vector<Worker*>(), std::vector<Order>());

}

MainWindow::~MainWindow()
{
    delete ui;
}
