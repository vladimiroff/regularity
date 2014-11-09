#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "factory.h"
#include <map>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::map<std::string,int> storageItems;
    storageItems["\\w"] = 10;
    storageItems["[aeoui]"] = 3;
    storageItems[".?"] = 3;
    storageItems["\\d"] = 7;
    storageItems["\\"] = 4;
    storageItems["?"] = 2;
    storageItems["a"] = 2;
    storageItems["\\w\\d"] = 5;
    Storage* storage = new Storage(storageItems);
    Factory* factory = new Factory(storage, 0, 30, 1, 20, 10, 0,  std::vector<Worker*>(), std::map<std::size_t, Order*>());
    this->factory = factory;

    //signals
    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    connect(factory, SIGNAL(moneyChanged(int)), this, SLOT(onMoneyChanged(int)));
    connect(factory, SIGNAL(orderCreated(int)), this, SLOT(onOrderCreated(int)));
    connect(factory, SIGNAL(orderRemoved(int)), this, SLOT(onOrderRemoved(int)));
    connect(ui->takeOrder, SIGNAL(clicked()), this, SLOT(onOrderTaken()));

    factory->add_money(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Factory* MainWindow::GetFactory() {
   return this->factory;
}

void MainWindow::onMoneyChanged(int money) {
    ui->money->display((int)money);
}

void MainWindow::onOrderCreated(int order_id) {
    ui->orderQueueLength->display(ui->orderQueueLength->intValue() + 1);
}

void MainWindow::onOrderRemoved(int order_id) {
    ui->orderQueueLength->display(ui->orderQueueLength->intValue() - 1);
}

void MainWindow::toggleMainViews() {
    int currentIndex = ui->mainViews->currentIndex();
    if (currentIndex) {
        ui->mainViews->setCurrentIndex(0);
        ui->toggleMainViewButton->setText("Shop");
    } else {
        ui->mainViews->setCurrentIndex(1);
        ui->toggleMainViewButton->setText("Workbench");
    }
}

void MainWindow::onOrderTaken() {
    int id = factory->take_order();
    factory->remove_order(id);
    Order* order = factory->get_order_in_progress();
    QString text(order->get_words()[0].c_str());
    ui->orderInfo->setText(text);
}

