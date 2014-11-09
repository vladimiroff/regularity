#include "factory.h"
#include "storage.h"

size_t PRICE_FOR_WORKER = 30;

Factory::Factory(Storage* storage, std::size_t money, float rating, std::size_t level, std::size_t factory_experience,
                 std::size_t level_experience, std::size_t current_order_id = 0,
                 std::vector<Worker*> workers = std::vector<Worker*>(),
                 std::map<std::size_t, Order> orders = std::map<std::size_t, Order>())
{
       workers_ = workers;
       orders_ = orders;
       storage_.reset(storage);
       money_ = money;
       rating_ = rating;
       level_ = level;
       factory_experience_ = factory_experience;
       level_experience_ = level_experience;
       current_order_id_ = current_order_id;
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
    orders_.insert(std::pair<std::size_t, Order>(current_order_id_, order));
    current_order_id_++;
}

void Factory::remove_order(std::size_t order_id)
{
    orders_.erase(order_id);
}

void Factory::set_orders(std::map<std::size_t, Order> orders)
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

void Factory::add_money()
{
    money_ += 100;
    qDebug() << "money added";
    emit this->moneyChanged(money_);
}

void Factory::buyWork()
{
    money_ -= PRICE_FOR_WORKER;
    workers_.push_back(new Worker(storage_.get()));
}

std::string Factory::takePart(std::string regexp)
{
    if(storage_->get_material(regexp))
        return regexp;
    else
        qDebug() << "Dont have this element";
}

void Factory::levelUp()
{
    level_up();
}


bool Factory::buyParts(std::string regexp, std::size_t quantity, Store store)
{
        std::size_t price = store[level_][regexp]->price;

        if (store[level_].find(regexp) != store[level_].end() && money_ >= quantity * price )
        {
            for(size_t i = 0; i < quantity; i++)
            {
                money_ -= price;
                storage_->add_material(regexp);
            }
            return true;
        }
        else
        {
            return false;
        }
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

void Factory::set_current_order_id(size_t id)
{
    current_order_id_ = id;
}

void Factory::experience_increase(std::size_t experience)
{
    factory_experience_ += experience;
}

void Factory::level_up()
{
    level_++;
    level_experience_ *= 2;
}

void Factory::create_order(std::vector<std::string> words, Client client, std::size_t price, std::size_t experience,
                           std::string solution = "")
{
    Order new_order(words, SENT, price, experience, client, solution);
    add_order(new_order);
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

std::map<std::size_t, Order> Factory::get_orders()
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

std::size_t Factory::get_current_id()
{
   return current_order_id_;
}

// public slots

