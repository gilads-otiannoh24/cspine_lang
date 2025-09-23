#include "token.h"
#include <vector>
#include <cctype>
#include <stdexcept>
#include <algorithm>

std::vector<Token> tokenize(const std::string &input)
{
    std::vector<Token> tokens;
    size_t i = 0;
    std::vector<std::string> keychars = {"+", "-", "*", "/", "(", ")"};

    while (i < input.size())
    {
        char c = input[i];

        if (std::isspace(c))
        {
            // skip whitespace
            i++;
            continue;
        }

        if (std::isdigit(c))
        {
            // capture full number (multi-digit too)
            std::string num;
            while (i < input.size() && std::isdigit(input[i]))
            {
                num.push_back(input[i]);
                i++;
            }
            tokens.emplace_back(TokenType::NUMBER, num);
            continue;
        }

        switch (c)
        {
        case '+':
            tokens.emplace_back(TokenType::PLUS, "+");
            break;
        case '-':
            tokens.emplace_back(TokenType::MINUS, "-");
            break;
        case '*':
            tokens.emplace_back(TokenType::STAR, "*");
            break;
        case '/':
            tokens.emplace_back(TokenType::SLASH, "/");
            break;
        case '(':
            tokens.emplace_back(TokenType::LPAREN, "(");
            break;
        case ')':
            tokens.emplace_back(TokenType::RPAREN, ")");
            break;
        default:
            // capture full number (multi-digit too)
            std::string word;
            while (i < input.size() && !std::isspace(input[i]) && std::find(keychars.begin(), keychars.end(), std::string(1, input[i])) == keychars.end())
            {
                word.push_back(input[i]);
                i++;
            }
            tokens.emplace_back(TokenType::WORD, word);
            continue;
        }

        i++;
    }

    // Always add EOF token at the end
    tokens.emplace_back(TokenType::EOF_TOKEN, "");
    return tokens;
}
