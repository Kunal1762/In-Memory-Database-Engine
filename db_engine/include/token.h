#pragma once
#include<string>

enum class TokenType{
    IDENTIFIER,
    NUMBER,
    STRING,

    CREATE,
    TABLE,
    INSERT,
    INTO,
    VALUES,
    SELECT,
    FROM,
    WHERE,
    DELETE,

    INT_TYPE,
    STRING_TYPE,
    BOOL_TYPE,
    DOUBLE_TYPE,

    STAR,
    COMMA,
    LPAREN,
    RPAREN,
    EQUAL,
    SEMICOLON,

    END_OF_FILE,
    INVALID
};
struct Token{
    TokenType type;
    std::string text;

    Token(TokenType t, const std::string&txt)
    :type(t),text(txt){}
};