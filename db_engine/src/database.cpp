#include "../include/database.h"

bool Database::createTable(const std::string&name, const schema& s){
    if(tables.find(name)!=tables.end()) return false;

    tables[name]=std::make_unique<RowStorage>(s);
    return true;
}

bool Database::deleteTable(const std::string&name){
    return tables.erase(name)>0;
}

RowStorage* Database::getTable(const std::string& name){
    if(tables.find(name)==tables.end()) return nullptr;

    return tables[name].get();
}