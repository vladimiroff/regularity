#ifndef ORDER_H
#define ORDER_H

#include "client.h"
#include <string>
#include <vector>
#include <QObject>
#include <QListWidgetItem>

enum Status {SENT, RECEIVED, DONE, IN_PROGRESS, NOT_ENOUGH_PARTS};

struct Part {
    std::size_t price;
    std::string part;
};


class Order
{
public:
    Order(std::vector<std::string> words, Status status, std::size_t experience,
          std::size_t price, Client client, std::string solution);
    Order(const Order&);
    vector<std::string> get_words();
    Status get_status();
    std::size_t get_experience();
    std::size_t get_price();
    Client get_client();
    std::string get_solution();

    void set_status(Status status);
    void set_experience(std::size_t experience);
    void set_price(std::size_t price);
    void set_client(Client client);
    void set_solution(std::string solution);

private:
    std::vector<std::string> words_;
    Status status_;
    std::size_t experience_;
    std::size_t price_;
    Client client_;
    std::string solution_;
};


#endif // ORDER_H
