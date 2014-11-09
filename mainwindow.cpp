#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "factory.h"
#include <map>
#include <stdio.h>
#include <QGridLayout>
#include <QRegExp>
#include <QList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    signalMapper = new QSignalMapper();

    //signals

    std::map<std::string,int> storageItems;
    storage = new Storage(storageItems);
    factory = new Factory(storage, 0, 30, 1, 20, 10, 0,  std::vector<Worker*>(), std::map<std::size_t, Order*>());
    factory->add_money(100);

    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    connect(factory, SIGNAL(moneyChanged(int)), this, SLOT(onMoneyChanged(int)));
    connect(factory, SIGNAL(orderCreated(int)), this, SLOT(onOrderCreated(int)));
    connect(factory, SIGNAL(orderRemoved(int)), this, SLOT(onOrderRemoved(int)));
    connect(ui->takeOrder, SIGNAL(clicked()), this, SLOT(onOrderTaken()));
    connect(storage, SIGNAL(addedMaterial(std::string)), this, SLOT(onAddedMaterial(std::string)));
    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onTookMaterial(QString)));
    connect(ui->check, SIGNAL(clicked()), this, SLOT(onCheck()));

    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("\\w");
    storage->add_material("[aeoui]");
    storage->add_material("[aeoui]");
    storage->add_material("[aeoui]");
    storage->add_material(".?");
    storage->add_material(".?");
    storage->add_material("\\d");
    storage->add_material("\\d");
    storage->add_material("\\d");
    storage->add_material("\\d");
    storage->add_material("a");
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
    if(id != -1) {
        factory->remove_order(id);
        Order* order = factory->get_order_in_progress();
        QString text(order->get_words()[0].c_str());
        ui->orderInfo->setText(text);
    }
}

void MainWindow::onAddedMaterial(std::string material)
{
    std::map<std::string,int>::const_iterator it = storage->materials().find(material);
    if(it != storage->materials().end()) {
        QString buttonName(material.c_str());
        QPushButton* pb = ui->storage->findChild<QPushButton*>(buttonName);

        if(pb == 0) {
            int buttons = storage->materials().size();
            QPushButton *pb = new QPushButton(buttonName);
            pb->setObjectName(buttonName);
            connect(pb, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(pb, buttonName);
            ui->storageLayout->addWidget(pb, buttons / 8, buttons % 8);
        }
    }
}

void MainWindow::onTookMaterial(QString material)
{
    std::string stdMaterial = material.toStdString();
    std::map<std::string,int>::const_iterator it = storage->materials().find(stdMaterial);

    if(it == storage->materials().end()) {
        return;
    }

    QPushButton* pb = ui->storage->findChild<QPushButton*>(material);
    if(pb == 0) {
        qDebug() << "Button with name " << material << " is missing!";
        return;
    }

    storage->get_material(stdMaterial);
    if(it->second <= 0) {
        pb->setDisabled(true);
        delete pb;
    }
    ui->answer->setText(ui->answer->text() + material);
}

void MainWindow::onCheck() {
    std::string expression = ui->answer->text().toStdString();
    Order* order = factory->get_order_in_progress();
    std::vector<std::string> words = order->get_words();
    if(factory->validateRegExp(expression, words)) {
        ui->answer->setText("Great job!");
        factory->add_money(order->get_price());
        factory->rating_increase(order->get_experience());
    }
    else {
        ui->answer->setText("You suck at this!");
        factory->rating_decrease(order->get_experience());
    }
}
