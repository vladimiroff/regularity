#include "worker.h"
#include <regex>
#include <vector>
#include <map>

Worker::Worker(Storage* storage)
{
   storage_.reset(storage);
}

bool check_matching(std::vector<std::string> words, std::regex expression)
{
    for(std::string word : words) {
        if(!std::regex_match(word, expression)) {
            return false;
        }
    }
    return true;
}

bool starting_with(std::vector<std::string> words, std::regex expression)
{
    for(std::string word : words) {
        if(!std::regex_search(word, expression)) {
            return false;
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
            start = begin + material;;
            if(check_matching(order.get_words(), regex(start))) {
                order.set_solution(start);
                return true;
            }
            else {
                if(starting_with(order.get_words(), regex(start))) {
                    beginings.push_back(start);
                }
            }
        }
        beginings.erase(beginings.begin());
    }

    return false;
}
