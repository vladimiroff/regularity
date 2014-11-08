#include "client.h"
#include "order.h"

size_t EXP_FOR_ORDER = 10;
size_t MONEY_FOR_ORDER = 30;

Client::Client()
{
    patience_ = 0;
    words_ = vector<string>();
    level_ = 0;
}
Client::Client(size_t patience, vector<string> words, size_t level)
{
    patience_ = patience;
    words_ = words;
    level_ = level;
}


size_t Client::get_patience() const
{
    return patience_;
}
vector<string> Client::get_words() const
{
    return words_;
}
size_t Client::get_level() const
{
    return level_;
}

void Client::set_patience(const size_t patience)
{
    if(patience > 0)
        patience_ = patience;
}
void Client::set_words(const vector<string> words)
{
    if(words.size() != 0)
        words_ = words;
}
void Client::set_level(const size_t level)
{
    level_ = level;
}


void Client::generate_order(Factory facory_for_order)
{
    //need to set random words in vector not 1st word !!!!!
    size_t order_level = level_ * EXP_FOR_ORDER;
    size_t order_money = level_ * MONEY_FOR_ORDER;
    Order order_to_push(words[1], "SENT", order_level, order_money, *this);
    facory_for_order.add_order(order_to_push);
}