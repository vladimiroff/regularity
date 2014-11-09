#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <mutex>
#include <QObject>

class Storage : public QObject
{
    Q_OBJECT
public:
    Storage(std::map<std::string,int>);

    void add_material(std::string);
    bool get_material(std::string);

    const std::map<std::string, int> &materials() const;

signals:
    void addedMaterial(std::string);
    void tookMaterial(std::string);

private:
    std::map<std::string,int> materials_;
    std::mutex materials_mutex_;
};

#endif // STORAGE_H
