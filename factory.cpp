#include "factory.h"

Factory::Factory(Storage storage, std::size_t money, float rating, std::size_t level, std::vector<Worker> workers = std::vector<Worker>(),std::vector<Order> orders = std::vector<Order>())
{
       workers_ = workers;
       orders_ = orders;
       storage_ = storage;
       money_ = money;
       rating_ = rating;
       level_ = level;
}

void Factory::add_worker(Worker worker)
{
    workers_.push_back(worker);
}

void Factory::remove_worker()
{
    workers_.pop_back();
}

void Factory::add_order(Order order)
{
    orders_.push_back(order);
}

void Factory::remove_order()
{
    orders_.pop_back();
}

void buy_part() {

}
