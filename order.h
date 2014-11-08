#ifndef ORDER_H
#define ORDER_H

#include "client.h"
#include <string>
#include <vector>

enum Status {SENT, RECEIVED, DONE, IN_PROGRESS, NOT_ENOUGH_PARTS};

struct Part {
    std::size_t price;
    std::string part;
};


class Order
{
public:
    Order(std::vector<std::string> word, Status status, std::size_t xp, std::size_t price, Client client,
          std::string solution);

    vector<std::string> get_words();

    void set_solution(std::string);

private:
    std::vector<std::string> words_;
    Status status_;
    std::size_t experience_;
    std::size_t price_;
    Client client_;
    std::string solution_;
};


#endif // ORDER_H
