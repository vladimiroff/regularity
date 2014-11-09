#include "factory.h"
#include "storage.h"
#include <QDebug>

size_t PRICE_FOR_WORKER = 30;

Factory::Factory(Storage* storage, std::size_t money, float rating, std::size_t level, std::size_t factory_experience,
                 std::size_t level_experience, std::size_t current_order_id,
                 std::vector<Worker*> workers,
                 std::map<std::size_t, Order*> orders)
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

void Factory::add_order(Order* order)
{
    order->set_status(RECEIVED);
    orders_.insert(std::pair<std::size_t, Order*>(current_order_id_, order));
    emit orderCreated(current_order_id_);
    current_order_id_++;
}

void Factory::remove_order(std::size_t order_id)
{
    orders_.erase(order_id);
    emit orderRemoved(order_id);
}

void Factory::set_orders(std::map<std::size_t, Order*> orders)
{
    orders_ = orders;
}

bool Factory::buy_part(std::string part, Store store)
{
    if (store.find(part) != store.end() && money_ >= store[part])
    {
        money_ -= store[part];
        emit this->moneyChanged(money_);
        storage_->add_material(part);
        return true;
    }
    else
    {
        return false;
    }
}

void Factory::add_money(std::size_t additional_money)
{
    money_ += additional_money;
    emit moneyChanged(money_);
}

void Factory::buyWork()
{
    money_ -= PRICE_FOR_WORKER;
    workers_.push_back(new Worker(storage_.get()));
}

std::string Factory::takePart(std::string regexp)
{
    if(storage_->get_material(regexp)) {
        return regexp;
    }
    else {
        return "";
    }
}

void Factory::levelUp()
{
    level_up();
    emit this->levelUp(get_level());
}

bool Factory::buyParts(std::string regexp, std::size_t quantity, Store store)
{
        std::size_t price = store[regexp];

        if (store.find(regexp) != store.end() && money_ >= quantity * price )
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
    emit moneyChanged(money_);
}

void Factory::rating_increase(float increase)
{
    rating_ += increase;
    emit ratingChanged(rating_);
}

void Factory::rating_decrease(float decrease)
{
    rating_ = rating_ - decrease;
    if (rating_ < 0) {
        rating_ = 0;
    }
    emit ratingChanged(rating_);
}

void Factory::set_rating(float new_rating)
{
    rating_ = new_rating;
    emit ratingChanged(rating_);
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

void Factory::create_order(std::vector<std::string> words, Client& client, std::size_t price, std::size_t experience,
                           std::string solution = "")
{
    Order* new_order = new Order(words, SENT, price, experience, client, solution);
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

std::map<std::size_t, Order*> Factory::get_orders()
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

void Factory::workOnOrder(size_t order_id)
{

    if(orders_.find(order_id) != orders_.end())
    {
        orders_[order_id]->set_status(IN_PROGRESS);
    }
}

bool Factory::validateRegExp(std::string expression, std::vector<std::string> words)
{
    QString qexpression(expression.c_str());
    QRegExp r(qexpression);
    if(!r.isValid())
    {
        return false;
    }
    for(std::string word : words)
    {
        QString qword(word.c_str());
        if(!r.exactMatch(qword))
        {
            return false;
        }
    }
    return true;
}

Order* Factory::get_order_in_progress() {
    return order_in_progress_;
}

int Factory::take_order() {
    if(orders_.size() > 0) {
        Order* order = orders_.begin()->second;
        order_in_progress_ = order;
        return orders_.begin()->first;
    }
    return -1;
}
