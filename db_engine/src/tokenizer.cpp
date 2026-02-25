#include "../include/tokenizer.h"
#include<unordered_map>
#include<cctype>

static std::unordered_map<std::string,TokenType>Keywords={
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
    {"DOUBLE", TokenType::DOUBLE_TYPE}
};