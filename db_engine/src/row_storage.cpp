#include "../include/row_storage.h"
#include "../include/value.h"

bool RowStorage::insert( const row& r){
    row temp=r;
    if(!validate(temp)){
        return false;
    }
    int pIndex=tableDef.getPrimaryKeyIndex();
    int pk=std::get<int>(temp.get(pIndex));
    if(index.count(pk)){
        return false;
    }
    int rowId=nextRowId++;
    int slotIndex;

    if(!freeSlots.empty()){
        slotIndex=freeSlots.back();
        freeSlots.pop_back();

        rows[slotIndex]=slot(r);
    }
    else{
        slotIndex=rows.size();
        rows.emplace_back(r);

    }

    index[pk]=rowId;
    rowIdtoSlotIndex[rowId]=slotIndex;
    // index[pk] = rows.size() - 1;
    return true;
}

row* RowStorage::find(int pk){
    auto it = index.find(pk);
    if (it == index.end()) return nullptr;

    int rowId=it->second;
    int slotIndex=rowIdtoSlotIndex[rowId];
    if(!rows[slotIndex].occupied){
        return nullptr;
    }
    return &rows[slotIndex].data;
}

bool RowStorage::remove(int pk){
    auto it = index.find(pk);
    if (it == index.end()) return false;

    int rowId=index[pk];
    int slotIndex=rowIdtoSlotIndex[rowId];

    rows[slotIndex].occupied=false;

    freeSlots.push_back(slotIndex);

    index.erase(pk);
    rowIdtoSlotIndex.erase(rowId);

    // size_t pos = it->second;
    // size_t last = rows.size() - 1;

    // if (pos != last) {
    //     int pIndex=tableDef.getPrimaryKeyIndex();
    //     rows[pos] = rows[last];
    //     int lastpk=std::get<int>(rows[last].get(pIndex));
    //     index[lastpk] = pos;
    // }

    // rows.pop_back();
    // index.erase(pk);
    return true;
}

bool RowStorage::validate(row& r){
    size_t rowSize=r.get_size();
    if(rowSize!=tableDef.columnCount()){
        return false;
    }
    for(int i=0; i<rowSize; i++){
        if(getValtype(r.get(i))!=tableDef.getColumnType(i)){
            return false;
        }
    }
    return true;
}

bool RowStorage::update(int pk, size_t columnIndex, const Value& val){
    if(index.find(pk)==index.end()){
        return false;
    }
    if(columnIndex==tableDef.getPrimaryKeyIndex()){
        return false;
    }
    if(getValtype(val)!=tableDef.getColumnType(columnIndex)){
        return false;
    }
    int rowid=index[pk];
    int slotIndex=rowIdtoSlotIndex[rowid];

    if(!rows[slotIndex].occupied){
        return false;   
    }
    rows[slotIndex].data.set(columnIndex,val);
    return true;

}

row* RowStorage::getRowById(int id){
    if(rowIdtoSlotIndex.find(id)==rowIdtoSlotIndex.end()){
        return nullptr;
    }
    size_t slotIndex=rowIdtoSlotIndex[id];
    if(!rows[slotIndex].occupied){
        return nullptr;
    }
    return &rows[slotIndex].data;
}

std::vector<row*>RowStorage::scan(){
    std::vector<row*>res;

    for(auto it:rows){
        if(it.occupied){
            res.push_back(&it.data);
        }
    }
    return res;
}