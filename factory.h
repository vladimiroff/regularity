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
    vector<Worker>      workers_;
    vector<Order>       orders_;
    Storage             storage_;
    size_t              money_;
    float               rating_;
    size_t              level_;

public:
    Factory(vector<Worker>, vector<Order>, Storage, size_t, float, size_t);

    void add_worker(Worker);
    void remove_worker();

    void add_order(Order);
    void remove_order();

    void buy_part();

    void add_money(size_t);

    void rating_increase(float);
    void rating_decrease(float);

    void level_up();
};



#endif // FACTORY_H
