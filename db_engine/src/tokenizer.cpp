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
    {"DOUBLE", TokenType::DOUBLE_TYPE},
    {"TRUE",TokenType::BOOLEAN},
    {"FALSE",TokenType::BOOLEAN}};

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

    char c=currentChar();

    if(std::isalpha(c)){
        return identifier();
    }
    if(std::isdigit(c)){
        return number();
    }
    if(c=='"'){
        return stringLiteral();
    }
    
    switch(c){
        case '>':
        if (peekChar() == '=') {
            pos += 2;
            return Token(TokenType::GREATER_EQUAL, ">=");
        }
        pos++;
        return Token(TokenType::GREATER, ">");

        case '<':
            if (peekChar() == '=') {
                pos += 2;
                return Token(TokenType::LESS_EQUAL, "<=");
            }
            pos++;
            return Token(TokenType::LESS, "<");

        case '!':
            if (peekChar() == '=') {
                pos += 2;
                return Token(TokenType::NOT_EQUAL, "!=");
            }
            pos++; 
            return Token(TokenType::INVALID, "!");

        case '*':pos ++;return {TokenType::STAR,"*"};
        case '(':pos++;return {TokenType::LPAREN,"("};
        case ',':pos++;return {TokenType::COMMA,","};
        case ')':pos++;return {TokenType::RPAREN,")"};
        case '=':pos++;return {TokenType::EQUAL,"="};
        case ';':pos++;return {TokenType::SEMICOLON,";"};

        default: pos++;return {TokenType::INVALID, std::string(1,c)};
    }
    
}

Token Tokenizer::identifier(){
    size_t start=pos;

    while(!isAtEnd() &&(std::isalnum(currentChar())||currentChar()=='_')){
        pos++;
    }
    std::string text=input.substr(start,pos-start);
    std::string upper=text;
    for(char &c:upper) c=std::toupper(c);

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
    std::string literal=input.substr(start,pos-start);
    if(!isAtEnd())pos++;
    return {TokenType::STRING,literal};
}

char Tokenizer::peekChar() const{
    if(pos+1>=input.size())return '\0';
    return input[pos+1];
}