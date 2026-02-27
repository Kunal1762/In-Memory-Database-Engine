#pragma once
#include<vector>
#include<unordered_map>
#include "row.h"
#include "schema.h"
#include "slot.h"

class RowStorage{
    private:
    std::vector<slot>rows;
    std::unordered_map<int,int>index;
    std::unordered_map<int,size_t>rowIdtoSlotIndex;
    std::vector<int>freeSlots;
    schema tableDef;
    int nextRowId=0;
    public:
    RowStorage(schema s)
    : tableDef(std::move(s)){}

    bool insert( const row& r);
    row* find(int pk);
    // void update(int rid, string new_name);
    bool remove(int pk);
    bool validate( row& r);
    bool update(int pk, size_t columnIndex, const Value& val);
    row* getRowById(int id);
    std::vector<row*>scan();
    
};