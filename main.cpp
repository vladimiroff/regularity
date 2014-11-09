#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QString>
#include <QJsonObject>
#include "order.h"
#include "factory.h"

size_t EXP_FOR_ORDER = 10;
size_t MONEY_FOR_ORDER = 30;
size_t generate_order_price(Client client)
{
    return client.get_level() * MONEY_FOR_ORDER;
}
size_t generate_order_experiance(Client client)
{
    return client.get_level() * EXP_FOR_ORDER;
}
std::vector<std::string> generate_order_words(Client client)
{
    return client.get_words();
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/TaskList.qml")));

    QObject* task_list = component.create();

    QObject* orderList = task_list->findChild<QObject*>("rect")->findChild<QObject*>("Orders");

    Storage* storage = new Storage(std::map<std::string,int>());
    Factory* factory = new Factory(storage, 5, 1.2, 5, 2, 1, std::vector<Worker*>(), std::vector<Order>());

    engine.rootContext()->setContextObject(factory);

    QObject::connect(factory, SIGNAL(newOrder(const QString)), orderList, SLOT(onTrigger(QString)));
    emit factory->newOrder("panda");
    return app.exec();
}
