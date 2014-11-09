#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "storage.h"
#include "worker.h"
#include "order.h"
#include <regex>
#include <QRegExp>
#include <QString>
#include <QDebug>
#include <iostream>
#include "storage.h"
#include "worker.h"
#include "order.h"
#include "factory.h"
#include <regex>
#include <QRegExp>
#include <QString>
#include <algorithm>
#include <thread>
#include <unistd.h>

size_t EXP_FOR_ORDER = 10;
size_t MONEY_FOR_ORDER = 30;

size_t generate_order_price(Client client)
{
    return (client.get_level() + 1) * MONEY_FOR_ORDER;
}
size_t generate_order_experiance(Client client)
{
    return client.get_level() * EXP_FOR_ORDER;
}
//need to correct func because we need to return words from file for client level
std::vector<std::string> generate_order_words(Client client)
{
    return client.get_words();
}

void generate_orders(Factory* factory, Client clients[10]) {
    while(true) {
        int n = rand() % factory->get_level();
        int price = generate_order_price(clients[n]);
        int xp = generate_order_experiance(clients[n]);
        std::vector<std::string> client_words = clients[n].get_words();
        std::random_shuffle(client_words.begin(), client_words.end());
        std::vector<std::string> order_words;
        order_words.push_back(clients[n].get_words()[0]);
        order_words.push_back(clients[n].get_words()[1]);
        order_words.push_back(clients[n].get_words()[2]);
        factory->create_order(order_words, clients[n], xp, price, "");
        usleep(rand() % 10000000);
    }
}

int main(int argc, char* argv[])
{
    Client clients[10] = {
            Client(100, {"aaa", "bbb", "ggg"}, 0),
            Client(100, {"aaa", "bbb", "ggg"}, 1),
            Client(100, {"aaa", "bbb", "ggg"}, 2),
            Client(100, {"aaa", "bbb", "ggg"}, 3),
            Client(100, {"aaa", "bbb", "ggg"}, 4),
            Client(100, {"aaa", "bbb", "ggg"}, 5),
            Client(100, {"aaa", "bbb", "ggg"}, 6),
            Client(100, {"aaa", "bbb", "ggg"}, 7),
            Client(100, {"aaa", "bbb", "ggg"}, 8),
            Client(100, {"aaa", "bbb", "ggg"}, 9)
        };

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Factory* factory = w.GetFactory();
    std::thread sender(generate_orders, factory, clients);

    return a.exec();
}
