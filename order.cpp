#include "order.h"
#include <QDebug>

Order::Order(std::vector<std::string> words, Status status, std::size_t experience, std::size_t price, Client client,
             std::string solution = "")
{
    words_ = words;
    status_ = status;
    experience_ = experience;
    price_ = price;
    client_ = client;
    solution_ = solution;
}

vector<std::string> Order::get_words()
{
    return words_;
}


Status Order::get_status()
{
    return status_;
}

std::size_t Order::get_experience()
{
    return experience_;
}

std::size_t Order::get_price()
{
    return price_;
}

Client Order::get_client()
{
    return client_;
}

std::string Order::get_solution()
{
    return solution_;
}

// setters

void Order::set_status(Status status)
{
    status_ = status;
}

void Order::set_experience(std::size_t experience)
{
    experience_ = experience;
}

void Order::set_price(std::size_t price)
{
    price_ = price;
}

void Order::set_client(Client client)
{
    client_ = client;
}

void Order::set_solution(std::string solution)
{
    solution_ = solution;
}
