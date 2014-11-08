#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <mutex>

class Storage
{
public:
    Storage(std::map<std::string,int>);

    void add_material(std::string);
    bool get_marerial(std::string);

    std::map<std::string, int> materials() const;

private:
    std::map<std::string,int> materials_;
    std::mutex materials_mutex_;
};

#endif // STORAGE_H
