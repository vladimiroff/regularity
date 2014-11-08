#include "factory.h"
#include "storage.h"
#include <QDebug>


Factory::Factory(Storage* storage, std::size_t money, float rating, std::size_t level, std::size_t factory_experience,
                 std::size_t level_experience, std::vector<Worker*> workers = std::vector<Worker*>(),
                 std::vector<Order> orders = std::vector<Order>())
{
       workers_ = workers;
       orders_ = orders;
       storage_.reset(storage);
       money_ = money;
       rating_ = rating;
       level_ = level;
       factory_experience_ = factory_experience;
       level_experience_ = level_experience;
}

// TODO create destructor to delete workers

void Factory::add_worker(Worker *worker)
{
    workers_.push_back(worker);
}

void Factory::remove_worker()
{
    workers_.pop_back();
}

void Factory::set_workers(std::vector<Worker *> workers)
{
    workers_ = workers;
}

void Factory::add_order(Order order)
{
    orders_.push_back(order);
}

void Factory::remove_order()
{
    orders_.pop_back();
}

void Factory::set_orders(std::vector<Order> orders)
{
    orders_ = orders;
}

bool Factory::buy_part(Part part, Store store)
{
    if (store[level_].find(part.part) != store[level_].end() && money_ >= part.price)
    {
        money_ -= part.price;
        storage_->add_material(part.part);
        return true;
    }
    else
    {
        return false;
    }
}

void Factory::add_money(size_t additional_money) {
    money_ += additional_money;
    emit this->moneyChanged(money_);
}

void Factory::set_money(std::size_t money)
{
    money_ = money;
}

void Factory::rating_increase(float increase)
{
    rating_ += increase;
}

void Factory::rating_decrease(float decrease)
{
    rating_ += decrease;
}

void Factory::set_rating(float new_rating)
{
    rating_ = new_rating;
}

void Factory::experience_increase(std::size_t experience)
{
    factory_experience_ += experience;
}

void Factory::level_up()
{
    level_++;
}

void Factory::create_order(std::vector<std::string> words, Client client, std::size_t price, std::size_t experience,
                           std::string solution = "")
{
    Order new_order(words, SENT, price, experience, client, solution);
    orders_.push_back(new_order);
}

Factory::~Factory()
{
    for (Worker* worker : workers_)
    {
        delete worker;
    }
}

// get methods:
std::vector<Worker*> Factory::get_workers()
{
    return workers_;
}

std::vector<Order> Factory::get_orders()
{
    return orders_;
}

std::size_t Factory::get_money()
{
    return money_;
}

float Factory::get_rating()
{
    return rating_;
}

std::size_t Factory::get_level()
{
    return level_;
}

std::size_t Factory::get_factory_experience()
{
    return factory_experience_;
}

std::size_t Factory::get_level_experience()
{
    return level_experience_;
}
