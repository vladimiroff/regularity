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
    Factory* factory = new Factory(storage, 100, 30, 0, 20, 10, 0,  std::vector<Worker*>(), std::map<std::size_t, Order*>());

}

MainWindow::~MainWindow()
{
    delete ui;
}
