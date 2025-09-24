#pragma once
#include <string>
#include <vector>
#include "token.h"
#include <unordered_map>

class Tokenizer
{
public:
    explicit Tokenizer(const std::string &source) : source(source), pos(0), tokens() {}
    std::vector<Token> tokenize();

    void show(); // For debugging

private:
    char peek() const;
    char advance();
    void skipWhitespace();
    Token number();
    Token word();
    std::string source;
    size_t pos;
    std::vector<Token> tokens;
    static const std::unordered_map<char, TokenInfo> singleCharTokens;
    bool matchSingleCharToken(char c);
};
