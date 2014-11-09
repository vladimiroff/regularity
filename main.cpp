#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "order.h"
#include "factory.h"

#include <iostream>
#include <algorithm>
#include "storage.h"
#include "worker.h"
#include "order.h"
#include <regex>
#include <QRegExp>
#include <QString>
#include <thread>
#include <unistd.h>

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
//need to correct func because we need to return words from file for client level
std::vector<std::string> generate_order_words(Client client)
{
    return client.get_words();
}

void generate_orders(Factory* factory, Client clients[10]) {
    while(true) {
        int n = rand() % 10;
        int price = generate_order_price(clients[n]);
        int xp = generate_order_experiance(clients[n]);
        std::random_shuffle(clients[n].get_words().begin(), clients[n].get_words().end());
        std::vector<std::string> order_words;
        order_words.push_back(clients[n].get_words()[0]);
        order_words.push_back(clients[n].get_words()[1]);
        order_words.push_back(clients[n].get_words()[2]);
        factory->create_order(order_words, clients[n], xp, price, "");
        usleep(rand() % 5);
    }
}

int main()
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

    std::map<std::string,int> first;
    first["?"] = 5;
    first["\\d"] = 5;
    first["\\w\\w"] = 5;
    vector<std::string> words = {"bam3", "ham3"};
    Client client(20, words, 1);
    Order order(words, SENT, 150, 300, client, "");
    Storage* a = new Storage(first);
    Factory* factory = new Factory(a, 100, 30, 0, 20, 10);
    std::thread sender(generate_orders, factory, clients);

    Worker b(a);
    std::cout << b.execute_order(order) << std::endl;
    return 0;
}
