#ifndef WORKER_H
#define WORKER_H

#include "order.h"
#include "storage.h"
#include <memory>

class Worker
{
public:
    Worker(Storage *);

    bool execute_order(Order&);

private:
    std::unique_ptr<Storage> storage_;
};

#endif // WORKER_H
