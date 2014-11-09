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


public:
    virtual ~Factory();
    Factory(Storage *storage, std::size_t money, float rating, std::size_t level, std::size_t factory_experience,
            std::size_t level_experience, std::vector<Worker*> workers, std::vector<Order> orders);


    void add_worker(Worker* new_worker);
    void remove_worker();
    void set_workers(std::vector<Worker*> workers);      //set_workers using vector
    void add_order(Order new_order);
    void set_orders(std::vector<Order> orders);          //set_orders using vector
    void remove_order(); 
    void add_money(std::size_t additional_money);
    void set_money(std::size_t money);                  //set_money
    void rating_increase(float additional_rating);
    void rating_decrease(float less_rating);
    void set_rating(float new_rating);                  //set_rating
    void create_order(std::vector<std::string> words, Client client, std::size_t experience,
                      std::size_t price, std::string string);
    void experience_increase(std::size_t additional_experience);
    void level_up();
    bool buy_part(Part part, Store store);



    // get methods
    std::vector<Worker*> get_workers();
    std::vector<Order> get_orders();
    std::size_t get_money();
    float get_rating();
    std::size_t get_level();
    std::size_t get_factory_experience();
    std::size_t get_level_experience();


public slots:
    Q_INVOKABLE void add_money();
    Q_INVOKABLE void buyWork();
    Q_INVOKABLE std::string takePart(std::string regexp);

signals:
    void moneyChanged(std::size_t);

private:
    std::vector<Worker*>        workers_;
    std::vector<Order>          orders_;
    std::unique_ptr<Storage>    storage_;
    std::size_t                 money_;
    float                       rating_;
    std::size_t                 level_;
    std::size_t                 factory_experience_;        //this is our xp
    std::size_t                 level_experience_;          //this is xp you need for next level
};



#endif // FACTORY_H
