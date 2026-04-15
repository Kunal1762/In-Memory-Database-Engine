#pragma once

#include<vector>
#include "include/token.h"
#include "../ast/statement.h"
#include "../ast/select_stmt.h"

class Parser{
    private:
    std::vector<Token>tokens;
    size_t current;

    Statement* parseStatement();

    Statement* parseSelect();
    Statement* parseInsert();
    Statement* parseCreate();
    Statement* parseDelete();   

    bool match(TokenType type);
    Token& advance();
    Token& peek();
    bool isAtEnd();
    public:
    Parser(const std::vector<Token>&tokens);
    Statement* parse();
};
