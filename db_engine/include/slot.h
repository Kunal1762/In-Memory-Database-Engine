#pragma once
#include "row.h"

struct slot{
    bool occupied;
    row data;

    slot(const row& r)
    : occupied(true), data(r){}
};