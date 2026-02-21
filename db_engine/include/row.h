#pragma once
#include <vector>
#include <iostream>
#include "value.h"

class row
{
private:
    std::vector<Value> values;

public:
    row(std::vector<Value> vals)
        : values(std::move(vals)) {}

    const Value& get(size_t idx) const{
        return values[idx];
    }
    Value& get(size_t idx){
        return values[idx];
    }
    size_t get_size(){
        return values.size();
    }
    bool set(size_t indx, const Value& val){
        values[indx]=val;
        return true;
    }
    
};