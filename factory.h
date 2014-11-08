#ifndef FACTORY_H
#define FACTORY_H

#include "worker.h"
#include "order.h"
#include "storage.h"

#include <QQuickItem>
#include <QtQuick>
#include <vector>
#include <map>
#include <memory>

// index of vector is level and map is parts in store for this level
typedef std::vector<std::map<std::string, Part>> Store;

class Factory : public QQuickItem
{
    Q_OBJECT

    std::vector<Worker*>        workers_;
    std::vector<Order>          orders_;
    std::unique_ptr<Storage>    storage_;
    std::size_t                 money_;
    float                       rating_;
    std::size_t                 level_;
    std::size_t                 factory_experience_;     //this is our xp
    std::size_t                 level_experience_;               //this is xp you need for next level

public:
    Factory(Storage *, std::size_t, float, std::size_t, std::size_t, std::size_t, std::vector<Worker*>, std::vector<Order>);
    virtual ~Factory();

    void add_worker(Worker*);
    void remove_worker();

    void add_order(Order);
    void remove_order();

    bool buy_part(Part part, Store store);


    void rating_increase(float);
    void rating_decrease(float);

    bool level_up();

    void create_order(std::vector<std::string>, Client client, std::size_t, std::size_t, string);
    void experience_increase(std::size_t);


    std::size_t get_money();

public slots:
    Q_INVOKABLE void add_money();

signals:
    void moneyChanged(std::size_t);
};



#endif // FACTORY_H
