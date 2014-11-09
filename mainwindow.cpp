#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "factory.h"
#include <map>
#include <stdio.h>
#include <QGridLayout>
#include <QRegExp>
#include <QList>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->storage->setWidgetResizable(true);
    signalMapper = new QSignalMapper();

    //signals
    std::map<std::string,int> storageItems;
    storage = new Storage(storageItems);
    factory = new Factory(storage, 0, 0, 1, 20, 10, 0,  std::vector<Worker*>(), std::map<std::size_t, Order*>());
    factory->add_money(100);

    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    connect(factory, SIGNAL(moneyChanged(int)), this, SLOT(onMoneyChanged(int)));
    connect(factory, SIGNAL(orderCreated(int)), this, SLOT(onOrderCreated(int)));
    connect(factory, SIGNAL(orderRemoved(int)), this, SLOT(onOrderRemoved(int)));
    connect(ui->takeOrder, SIGNAL(clicked()), this, SLOT(onOrderTaken()));
    connect(storage, SIGNAL(addedMaterial(std::string)), this, SLOT(onAddedMaterial(std::string)));
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onTookMaterial(QString)));
    connect(ui->check, SIGNAL(clicked()), this, SLOT(onCheck()));
    connect(factory, SIGNAL(ratingChanged(float)), this, SLOT(onRatingChanged(float)));

    disableInput();

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
    storage->add_material("[a-c]");
    storage->add_material("[d-f]");
    storage->add_material("[q-t]");
    storage->add_material("[l-s]");
    storage->add_material("[x-z]");

    ui->storageLayout->setContentsMargins(1, 1, 1, 1);

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
    ui->answer->setText("^");
    enableInput();
    int id = factory->take_order();
    if(id != -1) {
        factory->remove_order(id);
        Order* order = factory->get_order_in_progress();
        QStringList words;
        for (std::string word : order->get_words()) {
            words << QString(word.c_str());
        }
        ui->orderInfo->setText(words.join(", "));
        ui->takeOrder->setDisabled(true);
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
            QSize buttonSize(50, 50);
            ui->storageLayout->addWidget(pb, (buttons - 1) / 7, (buttons - 1) % 7);
            pb->setFixedSize(buttonSize);
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
        ui->answer->setText("Happy panda :)");
        factory->add_money(order->get_price());
        factory->rating_increase(order->get_experience());
    }
    else {
        ui->answer->setText("Sad panda :(");
        factory->rating_decrease(order->get_experience());
    }
    disableInput();
}

void MainWindow::disableInput() {
    ui->check->setDisabled(true);
    ui->storage->setDisabled(true);
    ui->answer->setDisabled(true);
    ui->takeOrder->setEnabled(true);

}

void MainWindow::enableInput() {
    ui->check->setEnabled(true);
    ui->storage->setEnabled(true);
    ui->takeOrder->setDisabled(true);
}

void MainWindow::onRatingChanged(float rating) {
    ui->xp->setValue(rating);
}
