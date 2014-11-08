#include "factory.h"

Factory::Factory(vector<Worker> workers = vector<Worker>(),vector<Order> _rders = vector<Order>(),
                 Storage storage, double money, int rating, int level) {
       workers_ = workers;
       orders_ = _rders;
       money_ = money;
       rating_ = rating;
       level_ = level;
}

void Factory::add_worker(Worker worker) {
    workers_.push_back(worker);
}

void Factory::remove_worker() {
    workers_.pop_back();
}

void Factory::add_order(Order order) {
    orders_.push_back(order);
}

void Factory::remove_order() {
    orders_.pop_back();
}


