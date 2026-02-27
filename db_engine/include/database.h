#pragma once
#include<unordered_map>
#include "row_storage.h"
#include<string>
#include<memory>
class Database{
    private:
    std::unordered_map<std::string, std::unique_ptr<RowStorage>>tables;
    public:
    bool createTable(const std::string& name, const schema& s);
    bool deleteTable(const std::string& name);
    RowStorage* getTable(const std:: string& name);

};