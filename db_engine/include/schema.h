#pragma once
#include<string>
#include<vector>
#include "types.h"

struct column
{
    std::string name;
    Type type;
};

class schema{
    public:
    schema(std::vector<column>cols, int pkInd)
    : columns(std::move(cols)),primaryIndex(std::move(pkInd))
    {
        
    }

    size_t columnCount() const{
        return columns.size();
    }

    const column& getcolum(size_t idx) const{
        return columns[idx];
    }
    const int getPrimaryKeyIndex(){
        return primaryIndex;
    }
    Type getColumnType(int i){
        return columns[i].type;
    }
    private:
    std::vector<column>columns;
    int primaryIndex;
};
