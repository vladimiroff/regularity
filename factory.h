#ifndef FACTORY_H
#define FACTORY_H

#include "worker.h"
#include "order.h"
#include "storage.h"
#include <vector>
#include <map>


using namespace std;

class Factory
{
    vector<Worker>      workers;
    vector<Order>       orders;
    Storage             storage;
    double              money;
    float               rating;
    int                 level;

public:
    Factory(vector<Worker>, vector<Order>, Storage, double, int, int);

    void add_worker(Worker);
    void remove_worker();

    void add_order(Order);
    void remove_order();

    void buy_part();

    void add_money(double);

    void rating_increase(float);
    void rating_decrease(float);

    void level_up();
};

Factory::Factory(vector<Worker> _workers = vector<Worker>(),vector<Order> _orders = vector<Order>(),
                 Storage _storage, double _money, int _rating, int _level) {
       workers = _workers;
       orders = _orders;
       money = _money;
       rating = _rating;
       level = _level;
}
#endif // FACTORY_H
