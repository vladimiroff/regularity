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
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->storage->setWidgetResizable(true);
    signalMapper = new QSignalMapper();
    shopSignalMapper = new QSignalMapper();
    //signals
    std::map<std::string,int> storageItems;
    storage = new Storage(storageItems);
    std::vector<Worker*> workers = {new Worker(storage)};
    factory = new Factory(storage, 0, 0, 1, 20, 10, 0,  workers, std::map<std::size_t, Order*>());
    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    connect(factory, SIGNAL(moneyChanged(int)), this, SLOT(onMoneyChanged(int)));
    connect(factory, SIGNAL(orderCreated(int)), this, SLOT(onOrderCreated(int)));
    connect(factory, SIGNAL(orderRemoved(int)), this, SLOT(onOrderRemoved(int)));
    connect(factory, SIGNAL(ratingChanged(float)), this, SLOT(onRatingChanged(float)));
    connect(factory, SIGNAL(levelChanged(int)), this, SLOT(onLevelChanged(int)));
    connect(ui->takeOrder, SIGNAL(clicked()), this, SLOT(onOrderTaken()));
    connect(storage, SIGNAL(addedMaterial(std::string)), this, SLOT(onAddedMaterial(std::string)));
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onTookMaterial(QString)));
    connect(ui->check, SIGNAL(clicked()), this, SLOT(onCheck()));
    connect(shopSignalMapper, SIGNAL(mapped(QString)), this, SLOT(onPartBought(QString)));
    connect(factory,SIGNAL(levelChanged(int)), this, SLOT(onLevelChanged(int)));
    connect(ui->worker_0, SIGNAL(clicked()), this, SLOT(onWork0Start()));
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
    storage->add_material(".?");
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
    store = {{"( ͡° ͜ʖ ͡°)", 9001}, {"\\w", 2}, {"\\d", 2}, {"\\s", 2}, {"\\W", 2},
            {"[abcdf]", 1}, {"[xyzt]", 1}, {"[qwerty]", 1},
            {"[aeiouy]", 1}, {"[jklmn]", 1}, {"?", 5}, {"|", 5}, {".", 5},
            {"+", 10}, {"*", 15}, {"[", 0},{"]", 0}};

    ui->storageLayout->setContentsMargins(1, 1, 1, 1);
    populateStore();
    onLevelChanged(1);
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
        ui->toggleMainViewButton->setText("Store");
    } else {
        ui->mainViews->setCurrentIndex(1);
        ui->toggleMainViewButton->setText("Workbench");
    }
}

void MainWindow::onOrderTaken() {
    ui->answer->setText("^");
    enableInput();
    int id = factory->take_order();
    if(id == -1) {
        ui->orderInfo->setText("");
        disableInput();
    } else {
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
            QSize buttonSize(90, 70);
            ui->storageLayout->addWidget(pb, (buttons - 1) / 7, (buttons - 1) % 7);
            pb->setFixedSize(buttonSize);
        } else if (!pb->isEnabled()) {
            pb->setEnabled(true);
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
        return;
    }

    storage->get_material(stdMaterial);
    if(it->second <= 0) {
        pb->setDisabled(true);
    }
    ui->answer->setText(ui->answer->text() + material);
}

void MainWindow::onCheck() {
    std::string expression = ui->answer->text().toStdString();
    Order* order = factory->get_order_in_progress();
    std::vector<std::string> words = order->get_words();
    if(factory->validateRegExp(expression, words)) {
        ui->answer->setText("You just made a panda happy :)");
        factory->add_money(order->get_price());
        factory->rating_increase(order->get_experience());
    }
    else {
        ui->answer->setText("You just made a panda sad :(");
        factory->rating_decrease(order->get_experience());
    }
    disableInput();
}

void MainWindow::disableInput()
{
    ui->check->setDisabled(true);
    ui->storage->setDisabled(true);
    ui->answer->setDisabled(true);
    ui->takeOrder->setEnabled(true);

}

void MainWindow::enableInput()
{
    ui->check->setEnabled(true);
    ui->storage->setEnabled(true);
    ui->takeOrder->setDisabled(true);
}

void MainWindow::onRatingChanged(float rating)
{
    ui->xp->setValue(rating);
}

void MainWindow::populateStore()
{

    int row = 0;
    int i = 0;
    for(auto item : store) {
        QString name(item.first.c_str());
        QString price(QString::number(item.second));
        QPushButton *button = new QPushButton(name);
        QLabel *label = new QLabel("$"+price);
        button->setObjectName(name);
        label->setObjectName(price);
        shopSignalMapper->setMapping(button, name);
        connect(button, SIGNAL(clicked()), shopSignalMapper, SLOT(map()));
        label->setAlignment(Qt::AlignCenter);
        ui->shopLayout->addWidget(button, row, i, Qt::AlignCenter);
        ui->shopLayout->addWidget(label, row+1, i, Qt::AlignCenter);
        QSize widgetSize(50, 50);
        button->setFixedSize(widgetSize);
        label->setFixedSize(widgetSize);
        i++;
        if(i == 9) {
            i = 0;
            row += 2;
        }
    }
}

void MainWindow::onPartBought(QString part)
{
    if(factory->buy_part(part.toStdString(), store)) {
        storage->add_material(part.toStdString());
    }
}

void MainWindow::onLevelChanged(int level) {
    ui->level->display((int) level);
}

void MainWindow::helper(Order* order, int i) {
    Worker* worker = factory->get_workers()[i];
    worker->execute_order(order);
}

void MainWindow::onWorker0Start() {
    if(factory->get_workers().size() > 0) {
        if(factory->get_orders().size() > 0) {
            Order* order = factory->get_orders()[0];
            Worker* worker = factory->get_workers()[0];
            std::thread work(helper, order, 0);
        }
    }
}
