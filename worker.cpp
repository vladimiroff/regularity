#include "worker.h"
#include <regex>
#include <vector>
#include <map>
#include <QRegExp>
#include <QString>
#include <iostream>

Worker::Worker(Storage* storage)
{
   storage_.reset(storage);
}

bool check_matching(std::vector<std::string> words, std::string expression)
{
    QString qexpression(expression.c_str());
    QRegExp r(qexpression);
    for(std::string word : words) {
        QString qword(word.c_str());
        if(!r.exactMatch(qword)) {
            return false;
        }
    }
    return true;
}

bool starting_with(std::vector<std::string> words, std::string expression)
{
    QString qexpression(expression.c_str());
    QRegExp r(qexpression);
    for(std::string word : words) {
        QString qword(word.c_str());
        if(r.isValid()) {
            if(r.indexIn(qword) < 0) {
                std::cout << r.indexIn("qword") << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool Worker::execute_order(Order& order)
{
    std::vector<std::string> beginings;
    beginings.push_back("^");
    std::map<std::string, int> materials_quantity = storage_->materials();
    std::vector<string> materials;
    for(const auto& material: materials_quantity) {
        materials.push_back(material.first);
    }

    for(const std::string& begin : beginings) {
        for(const std::string& material : materials) {
            std::string start;
            start = begin + material;
            if(check_matching(order.get_words(), start)) {
                order.set_solution(start);
                return true;
            }
            else {
                if(starting_with(order.get_words(), start)) {
                    beginings.push_back(start);
                }
            }
        }
        beginings.erase(beginings.begin());
    }

    return false;
}
