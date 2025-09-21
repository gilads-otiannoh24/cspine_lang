#include "token.h"
#include <vector>
#include <cctype>
#include <stdexcept>

std::vector<Token> tokenize(const std::string &input)
{
    std::vector<Token> tokens;
    size_t i = 0;

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
            throw std::runtime_error(std::string("Unexpected character: ") + c);
        }

        i++;
    }

    // Always add EOF token at the end
    tokens.emplace_back(TokenType::EOF_TOKEN, "");
    return tokens;
}
