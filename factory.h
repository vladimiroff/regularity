#ifndef FACTORY_H
#define FACTORY_H

#include "worker.h"
#include "order.h"
#include "storage.h"
#include <vector>
#include <map>




class Factory
{
    std::vector<Worker>      workers_;
    std::vector<Order>       orders_;
    Storage                  storage_;
    std::size_t              money_;
    float                    rating_;
    std::size_t              level_;

public:
    Factory(std::vector<Worker>, std::vector<Order>, Storage, std::size_t, float, std::size_t);

    void add_worker(Worker);
    void remove_worker();

    void add_order(Order);
    void remove_order();

    void buy_part();

    void add_money(std::size_t);

    void rating_increase(float);
    void rating_decrease(float);

    void level_up();
};



#endif // FACTORY_H
