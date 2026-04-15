#include "include/parser/parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>&tokens)
    :   tokens(tokens), current(0){}

Statement* Parser::parse(){
    return parseStatement();
}

Statement* Parser::parseStatement(){
    Token& token=peek();

    switch(token.type){
        case TokenType::SELECT:
            return parseSelect();
        case TokenType::CREATE:
            return parseCreate();
        case TokenType::INSERT:
            return parseInsert();
        case TokenType::DELETE:
            return parseDelete();
        default:
            throw std::runtime_error("Unexpected Statement");
    }
}

Statement* Parser:: parseSelect(){
    advance(); 

    if (!match(TokenType::STAR)) {
        throw std::runtime_error("Expected * after SELECT");
    }

    if (!match(TokenType::FROM)) {
        throw std::runtime_error("Expected FROM");
    }

    Token& tableToken = advance();

    if (tableToken.type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected table name");
    }

    SelectStmt* stmt = new SelectStmt();
    stmt->tableName = tableToken.text;

    return stmt;
}
Statement* Parser::parseCreate(){

}
Statement* Parser::parseInsert(){

}
Statement* Parser::parseDelete(){

}

Token& Parser::peek(){
    return tokens[current];
}
Token& Parser::advance(){
    if(!isAtEnd()) current++;
    return tokens[current-1];
}
bool Parser::match(TokenType type){
    if(peek().type==type){
        advance();
        return true;
    }
    return false;
}
bool Parser::isAtEnd(){
    return peek().type==TokenType::END_OF_FILE;
}