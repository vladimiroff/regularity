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

        int n = factory->get_level() - 1;
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
            Client(100, {"a", "b", "aa", "bb", "aaa", "dd", "ddd"}, 0),
            Client(100, {"rat", "hat", "bat", "cat", "mat", "pat", "wat"}, 1),
            Client(100, {"panda", "banda", "fanta", "lambda", "banana", "mana", "kanna"}, 2),
            Client(100, {"lol1", "larodi2", "lambda4", "lala6", "lada7", "word4", "world9", "plan9"}, 3),
            Client(100, {"p67eo", "e44o4", "r2d2", "a5x4sr", "r3k4a", "l3d1k"}, 4),
            Client(100, {"ka\\pa", "a\\ll", "xm\\l", "sla\\sh", "a\\rr"}, 5),
            Client(100, {"la   la", "spa ce", "o   pen", " almost there", "free doom"}, 6),
            Client(100, {"i am a dot.", "this should be hard!", "what?", "who?", "when?", "panda!", "mhm."}, 7),
            Client(100, {"[a]", "(d)", "{b}", "[b]", "{d}", "(w)"}, 8),
            Client(100, {"\\w\\d+", "\\d+\\d", ".*", "\\W+", "\\s\\s", "\\d*"}, 9)
        };

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Factory* factory = w.GetFactory();
    std::thread sender(generate_orders, factory, clients);

    return a.exec();
}
