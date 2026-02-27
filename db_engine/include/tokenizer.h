#pragma once
#include<string>
#include "token.h"

class Tokenizer{
    public:
    Tokenizer(const std::string&input);

    Token next();
    Token peek();

    size_t getPosition() const { return pos; }

    private:
    std::string input;
    size_t pos;

    void skipWhiteSpaces();
    bool isAtEnd() const;
    char currentChar() const;
    char peekChar() const;

    Token identifier();
    Token number();
    Token stringLiteral();

    
};