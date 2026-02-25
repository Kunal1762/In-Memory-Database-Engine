#include "../include/tokenizer.h"
#include <unordered_map>
#include <cctype>

static std::unordered_map<std::string, TokenType> Keywords = {
    {"CREATE", TokenType::CREATE},
    {"TABLE", TokenType::TABLE},
    {"INSERT", TokenType::INSERT},
    {"INTO", TokenType::INTO},
    {"VALUES", TokenType::VALUES},
    {"SELECT", TokenType::SELECT},
    {"FROM", TokenType::FROM},
    {"WHERE", TokenType::WHERE},
    {"DELETE", TokenType::DELETE},
    {"INT", TokenType::INT_TYPE},
    {"STRING", TokenType::STRING_TYPE},
    {"BOOL", TokenType::BOOL_TYPE},
    {"DOUBLE", TokenType::DOUBLE_TYPE}};

Tokenizer::Tokenizer(const std::string &in)
: input(in), pos(0) {};

bool Tokenizer::isAtEnd() const{
    return pos>=input.size();
}

char Tokenizer::currentChar() const{
    if(isAtEnd()) return '\0';
    return input[pos];
}
void Tokenizer::skipWhiteSpaces(){
    while(!isAtEnd() && std::isspace(currentChar())){
        pos++;
    }
}

Token Tokenizer::peek(){
    size_t savedPos=pos;
    Token t=next();
    pos=savedPos;
    return t;
}

Token Tokenizer::next(){

}