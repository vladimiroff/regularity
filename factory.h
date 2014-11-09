#ifndef FACTORY_H
#define FACTORY_H

#include "worker.h"
#include "order.h"
#include "storage.h"

#include <QObject>
#include <QString>
#include <vector>
#include <map>
#include <memory>

// index of vector is level and map is parts in store for this level
typedef std::map<std::string, std::size_t> Store;

class Factory : public QObject
{
    Q_OBJECT


public:
    virtual ~Factory();

    Factory(Storage *storage, std::size_t money, float rating, std::size_t level, std::size_t factory_experience,
            std::size_t level_experience, size_t current_order_id = 0,
            std::vector<Worker*> workers = std::vector<Worker*>(),
            std::map<std::size_t, Order*> orders = std::map<std::size_t, Order*>());

    void add_worker(Worker* new_worker);
    void remove_worker();
    void set_workers(std::vector<Worker*> workers);      //set_workers using vector
    void add_order(Order* new_order);
    void set_orders(std::map<size_t, Order*> orders);          //set_orders using vector
    void remove_order(std::size_t order_id);
    void set_money(std::size_t money);                  //set_money
    void rating_increase(float additional_rating);
    void rating_decrease(float less_rating);
    void set_rating(float new_rating);                  //set_rating
    void set_current_order_id(std::size_t id);
    void create_order(std::vector<std::string> words, Client& client, std::size_t experience,
                      std::size_t price, std::string string);
    void experience_increase(std::size_t additional_experience);
    void level_up();
    bool buy_part(Part part, Store store);
    int take_order();

    // get methods
    std::vector<Worker*> get_workers();
    std::map<size_t, Order*> get_orders();
    std::size_t get_money();
    float get_rating();
    std::size_t get_level();
    std::size_t get_factory_experience();
    std::size_t get_level_experience();
    std::size_t get_current_id();
    Order* get_order_in_progress();


public slots:
    Q_INVOKABLE void add_money(std::size_t);
    Q_INVOKABLE void buyWork();
    Q_INVOKABLE std::string takePart(std::string regexp);
    Q_INVOKABLE void levelUp();
    Q_INVOKABLE void workOnOrder(std::size_t order_id);
    Q_INVOKABLE bool buyParts(std::string regexp, std::size_t quantity, Store store);
    Q_INVOKABLE bool validateRegExp(std::string regexp, vector<std::string> words);

signals:
    void orderCreated(int);
    void orderRemoved(int);
    void moneyChanged(int);
    void ratingChanged(float);

private:
    std::vector<Worker*>            workers_;
    std::map<std::size_t, Order*>   orders_;
    std::unique_ptr<Storage>        storage_;
    std::size_t                     money_;
    float                           rating_;
    std::size_t                     level_;
    std::size_t                     factory_experience_;        //this is our xp
    std::size_t                     level_experience_;          //this is xp you need for next level
    std::size_t                     current_order_id_;
    Order*                          order_in_progress_;
};



#endif // FACTORY_H
