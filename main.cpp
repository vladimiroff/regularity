#include <QApplication>
#include <QQmlApplicationEngine>
#include "order.h"

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

    return app.exec();
}
