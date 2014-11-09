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
#include <algorithm>
#include "storage.h"
#include "worker.h"
#include "order.h"
#include "factory.h"
#include <regex>
#include <QRegExp>
#include <QString>
#include <thread>
#include <unistd.h>
#include <thread>
#include <unistd.h>
#include <random>

size_t EXP_FOR_ORDER = 50;
size_t MONEY_FOR_ORDER = 30;

size_t generate_order_price(Client client)
{
    return (client.get_level() + 1) * MONEY_FOR_ORDER;
}
size_t generate_order_experiance(Client client)
{
    return (client.get_level() + 1) * EXP_FOR_ORDER;
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


        std::vector<std::string> order_words;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(client_words.begin(), client_words.end(), std::default_random_engine(seed));

        for (std::string& word: client_words) {
            order_words.push_back(word);
            if(order_words.size() == 3){
                break;
            }
        }

        factory->create_order(order_words, clients[n], xp, price, "");

        usleep(2000 + (rand() % 10000000));
    }
}


int main(int argc, char* argv[])
{
    Client clients[10] = {
            Client(100, {"a", "b", "aa", "bb", "aaa"}, 0),
            Client(100, {"rat", "hat", "bat", "cat" }, 1),
            Client(100, {"panda", "banda", "fanta", "lambda", "banana"}, 2),
            Client(100, {"a1", "a2", "bb4", "bbb6xy", "a7xy"}, 3),
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
