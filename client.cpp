#include "client.h"

Client::Client()
{
    patience_ = 0;
    words_ = vector<string>();
    level_ = 0;
}

Client::Client(patience, words, level)
{
    patience_ = patience;
    words_ = words;
    level_ = level;
}

Client::~Client()
{

}

Client::Client(const Client& other)
{

}

Client Client::operator=(const Client& other)
{

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

void Client::set_patience(const size_t patience);
void Client::set_words(const vector<string> words);
void Client::set_level(const size_t level);

void clear()
{

}

void copy(const Client& other)
{
    patience_ = other.get_patience();
    words_ = other.get_words();

}

void Client::generate_order(Factory facory_for_order);
