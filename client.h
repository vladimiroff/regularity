#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "factory.h"

using namespace std;

class Client
{
public:
    Client();
<<<<<<< Updated upstream
    Client(size_t patience, vector<string> words, size_t level);
=======
    Client(size_t patience, vector<string>words, size_t level);
    ~Client();
    Client(const Client& other);
    Client operator=(const Client& other);
>>>>>>> Stashed changes

    size_t get_patience() const;
    vector<string> get_words() const;
    size_t get_level() const;

    void set_patience(const size_t patience);
    void set_words(const vector<string> words);
    void set_level(const size_t level);

    void generate_order(Factory facory_for_order);

private:
    size_t patience_;
    vector<string> words_;
    size_t level_;
};

#endif // CLIENT_H
