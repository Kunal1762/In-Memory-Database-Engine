#pragma once
#include "statement.h"
#include <string>

class SelectStmt : public Statement {
public:
    std::string tableName;

    SelectStmt() {
        type = StatementType::SELECT;
    }
};