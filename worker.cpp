#include "worker.h"
#include <regex>
#include <vector>
#include <map>

typedef pair<std::string, std::vector<std::string> > begining;

Worker::Worker(Storage* storage)
{
   storage_.reset(storage);
}

std::vector<std::string> Worker::execute_order(Order& order)
{
    std::vector<begining> beginings;
    beginings.push_back(begining("^", std::vector<std::string>()));
    std::map<std::string, int> materials_quantity = storage_->materials();
    std::vector<string> materials;
    for(const auto& material: materials_quantity) {
        materials.push_back(material.first);
    }

    for(const begining& begin : beginings) {
        for(const string& material : materials) {
            begining start;
            start.first = begin.first + material;
            start.second = begin.second;
            start.second.push_back(material);
            if(std::regex_match("kiro", std::regex(start.first))) {
                return start.second;
            }
            else {
                if(std::regex_search("kiro", regex(start.first))) {
                    beginings.push_back(start);
                }
            }
        }
        beginings.erase(beginings.begin());
    }

    return std::vector<std::string>();
}
