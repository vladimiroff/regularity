#include "storage.h"

Storage::Storage(std::map<std::string,int> materials)
{
    materials_ = materials;
}

void Storage::add_material(std::string material)
{
    materials_mutex_.lock();
    if(materials_.find(material) != materials_.end())
    {
        materials_[material] += 1;
    }
    else
    {
        materials_.insert(std::pair<std::string,int>(material,1));
    }
    materials_mutex_.unlock();
}

bool Storage::get_marerial(std::string material)
{
    materials_mutex_.lock();
    if(materials_.find(material) != materials_.end())
    {
        materials_[material] -= 1;
        materials_mutex_.unlock();
        return true;
    }
    else
    {
        materials_mutex_.unlock();
        return false;
    }
}

std::map<std::string,int> Storage::materials() const
{
    return materials_;
}


