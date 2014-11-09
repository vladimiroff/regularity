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
    storageItems["\\"] = 4;
    storageItems["?"] = 2;
    storageItems["a"] = 2;
    connect(ui->toggleMainViewButton, SIGNAL(clicked()), this, SLOT(toggleMainViews()));
    Storage* storage = new Storage(storageItems);
    Factory* factory = new Factory(storage, 100, 30, 0, 20, 10, 0,  std::vector<Worker*>(), std::map<std::size_t, Order*>());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleMainViews() {
    int currentIndex = ui->mainViews->currentIndex();
    QFont currentFont = ui->toggleMainViewButton->font();
    if (currentIndex) {
        ui->mainViews->setCurrentIndex(0);
        ui->toggleMainViewButton->setText("Shop");
        currentFont.setPointSize(currentFont.pointSize() + 5);
        currentFont.setPixelSize(currentFont.pixelSize() + 1);
    } else {
        ui->mainViews->setCurrentIndex(1);
        ui->toggleMainViewButton->setText("Workbench");
        currentFont.setPointSize(currentFont.pointSize() - 5);
        currentFont.setPixelSize(currentFont.pixelSize() - 1);
    }
    ui->toggleMainViewButton->setFont(currentFont);
}
