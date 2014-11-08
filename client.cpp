#include "client.h"
#include "order.h"

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
