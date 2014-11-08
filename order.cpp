#include "order.h"

Order::Order(std::vector<std::string> words, Status status, std::size_t experience, std::size_t price, Client client,
             std::vector<Part> solution = std::vector<Part>())
{
    words_ = words;
    status_ = status;
    experience_ = experience;
    price_ = price;
    client_ = client;
    solution_ = solution;
}
