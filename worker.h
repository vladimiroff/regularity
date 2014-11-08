#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <string>
#include <vector>
#include "factory.h"

using namespace std;

class Worker
{
public:
    Worker();
    Worker(patience, words, level);
    ~Worker();
    Worker(const Worker& other);
    Worker operator=(const Worker& other);

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

#endif // WORKER_H
