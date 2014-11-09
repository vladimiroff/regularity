#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "order.h"
#include "factory.h"

#include <iostream>
#include "storage.h"
#include "worker.h"
#include "order.h"
#include <regex>
#include <QRegExp>
#include <QString>

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

int main()
{
    std::map<std::string,int> first;
    first["?"] = 5;
    first["\\d"] = 5;
    first["\\w\\w"] = 5;
    vector<std::string> words = {"bam3", "ham3"};
    Client client(20, words, 1);
    Order order(words, SENT, 150, 300, client, "");

    Storage* a = new Storage(first);
    Worker b(a);
    std::cout << b.execute_order(order) << std::endl;
    return 0;
}
