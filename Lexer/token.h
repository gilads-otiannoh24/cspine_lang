#pragma once
#include <string>

enum class TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    WORD,
    EOF_TOKEN,
    END_OF_FILE,
    STORE,
    LINE_END,
    COMMA,
    SEMICOLON,

};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v) : type(t), value(v) {}
};

struct TokenInfo
{
    TokenType type;
    std::string value; // optional fixed value; if empty, we use the char itself
};