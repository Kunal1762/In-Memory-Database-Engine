#pragma once
#include<string>
#include<variant>
#include "types.h"

using Value=std::variant<int, double,bool, std::string>;

inline Type getValtype(const Value& v){
    if(std::holds_alternative<int>(v)){
        return Type::INT;
    }
    if(std::holds_alternative<std::string>(v)){
        return Type::STRING;
    }
    if(std::holds_alternative<double>(v)){
        return Type::DOUBLE;
    }
    if(std::holds_alternative<bool>(v)){
        return Type::BOOL;
    }
    throw std::runtime_error("Unsupported Value type");
}