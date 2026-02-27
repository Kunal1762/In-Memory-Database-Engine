#pragma once
#include<string>

enum class TokenType{
    IDENTIFIER,
    NUMBER,
    STRING,
    BOOLEAN,

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

    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,
    NOT_EQUAL,
    EQUAL_EQUAL,

    END_OF_FILE,
    INVALID
};
struct Token{
    TokenType type;
    std::string text;

    Token(TokenType t, const std::string&txt)
    :type(t),text(txt){}
};