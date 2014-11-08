#include "factory.h"
#include "storage.h"


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

void Factory::add_order(Order order)
{
    orders_.push_back(order);
}

void Factory::remove_order()
{
    orders_.pop_back();
}

bool Factory::buy_part(Part part, Store store) {
    if (store[level_].find(part.part) != store[level_].end() && money_ >= part.price) {
        money_ -= part.price;
        storage_->add_material(part.part);
        return true;
    } else {
        return false;
    }
}

void Factory::add_money(std::size_t money) {
    money_ += money;
}

void Factory::rating_increase(float increase)
{
    rating_ += increase;
}

void Factory::rating_decrease(float decrease) {
    rating_ += decrease;
}

void Factory::experience_increase(std::size_t experience) {
    factory_experience_ += experience;
}

bool Factory::level_up() {
    return true;
}

void Factory::create_order(std::vector<std::string> words, Client client, std::size_t price, std::size_t experience,
                  std::string solution = "") {
    Order new_order(words, SENT, price, experience, client, solution);
    orders_.push_back(new_order);
}
