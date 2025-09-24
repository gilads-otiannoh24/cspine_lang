#include "token.h"
#include "tokenizer.h"
#include <vector>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <unordered_map>

const std::unordered_map<char, TokenInfo> Tokenizer::singleCharTokens = {
    {'+', {TokenType::PLUS, "+"}},
    {'-', {TokenType::MINUS, "-"}},
    {'*', {TokenType::STAR, "*"}},
    {'/', {TokenType::SLASH, "/"}},
    {'(', {TokenType::LPAREN, "("}},
    {')', {TokenType::RPAREN, ")"}},
    {'=', {TokenType::STORE, "="}},
    {';', {TokenType::SEMICOLON, ";"}},
    {',', {TokenType::COMMA, ","}},
    {'\n', {TokenType::LINE_END, "\\n"}},
};

std::vector<Token> Tokenizer::tokenize()
{
    while (true)
    {
        skipWhitespace();
        char c = peek();
        if (c == '\0')
        {
            tokens.emplace_back(TokenType::EOF_TOKEN, "");
            break;
        }
        else if (std::isdigit(c))
        {
            tokens.push_back(number());
        }
        else if (std::isalpha(c) || c == '_')
        {
            tokens.push_back(word());
        }
        else if (!matchSingleCharToken(c))
        {
            throw std::runtime_error(std::string("Unexpected character: ") + c);
        }
    }

    return tokens;
}

bool Tokenizer::matchSingleCharToken(char c)
{
    auto it = Tokenizer::singleCharTokens.find(c);
    if (it != Tokenizer::singleCharTokens.end())
    {
        const auto &info = it->second;
        advance();
        std::string value = info.value.empty() ? std::string(1, c) : info.value;
        tokens.emplace_back(info.type, value);
        return true;
    }
    return false;
}

void Tokenizer::show()
{
    for (const auto &token : tokens)
    {
        std::string typeStr;
        switch (token.type)
        {
        case TokenType::NUMBER:
            typeStr = "NUMBER";
            break;
        case TokenType::PLUS:
            typeStr = "PLUS";
            break;
        case TokenType::MINUS:
            typeStr = "MINUS";
            break;
        case TokenType::STAR:
            typeStr = "STAR";
            break;
        case TokenType::SLASH:
            typeStr = "SLASH";
            break;
        case TokenType::LPAREN:
            typeStr = "LPAREN";
            break;
        case TokenType::RPAREN:
            typeStr = "RPAREN";
            break;
        case TokenType::WORD:
            typeStr = "WORD";
            break;
        case TokenType::STORE:
            typeStr = "STORE";
            break;
        case TokenType::EOF_TOKEN:
            typeStr = "EOF_TOKEN";
            break;
        default:
            typeStr = "UNKNOWN";
            break;
        }
        std::cout << "<" << typeStr << ", \"" << token.value << "\">\n";
    }
};

char Tokenizer::peek() const
{
    if (pos < source.size())
        return source[pos];
    return '\0'; // End of input
};

char Tokenizer::advance()
{
    if (pos < source.size())
        return source[pos++];
    return '\0'; // End of input
};

void Tokenizer::skipWhitespace()
{
    while (std::isspace(peek()))
        advance();
};

Token Tokenizer::number()
{
    std::string num;
    while (std::isdigit(peek()))
        num.push_back(advance());
    return Token(TokenType::NUMBER, num);
};
Token Tokenizer::word()
{
    std::string w;
    while (std::isalnum(peek()) || peek() == '_')
        w.push_back(advance());
    return Token(TokenType::WORD, w);
};
