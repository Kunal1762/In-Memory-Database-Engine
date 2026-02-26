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
    skipWhiteSpaces();
    if(isAtEnd()) return {TokenType::END_OF_FILE,""};

    char c=input[pos];

    if(std::isalpha(c)){
        return identifier();
    }
    if(std::isdigit(c)){
        return number();
    }
    if(c=='"'){
        return stringLiteral();
    }
    pos++;
    switch(c){
        case '*':return {TokenType::STAR,"*"};
        case '(':return {TokenType::LPAREN,"("};
        case ',':return {TokenType::COMMA,","};
        case ')':return {TokenType::RPAREN,")"};
        case '=':return {TokenType::EQUAL,"="};
        case ';':return {TokenType::SEMICOLON,";"};

        default: return {TokenType::INVALID, std::string(1,c)};
    }
    
}

Token Tokenizer::identifier(){
    size_t start=pos;

    while(!isAtEnd() &&(std::isalnum(currentChar())||currentChar()=='_')){
        pos++;
    }
    std::string text=input.substr(start,pos-start);
    std::string upper=text;
    for(char c:upper) c=std::toupper(c);

    if(Keywords.count(upper)){
        return {Keywords[upper],text};
    }
    return {TokenType::IDENTIFIER,text};
}

Token Tokenizer::number(){
    size_t start=pos;

    while(!isAtEnd() && std::isdigit(currentChar())){
        pos++;
    }

    return {TokenType::NUMBER,input.substr(start,pos-start)};
}

Token Tokenizer::stringLiteral(){
    pos++;
    size_t start=pos;

    while(!isAtEnd() && currentChar()!='"'){
        pos++;
    }
    if(!isAtEnd())pos++;
    return {TokenType::STRING,input.substr(start,pos-start)};
}