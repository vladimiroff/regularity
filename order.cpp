#include "order.h"

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

vector<std::string> Order::get_words() {
    return words_;
}

void Order::set_solution(std::string solution) {
    solution_ = solution;
}

