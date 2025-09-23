#include "../Lexer/token.h"
#include "ast.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

std::shared_ptr<ASTNode> Parser::parse()
{
    return parseExpression();
}

const Token Parser::peek() const
{
    if (pos < tokens.size())
        return tokens[pos];
    return Token(TokenType::END_OF_FILE, "");
}

const Token Parser::advance()
{
    if (pos < tokens.size())
        return tokens[pos++];
    return Token(TokenType::END_OF_FILE, "");
}

std::shared_ptr<ASTNode> Parser::parseExpression()
{
    auto node = parseTerm();

    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS)
    {
        Token op = advance();
        auto right = parseTerm();
        auto newNode = std::make_shared<ASTNode>(ASTNodeType::BinaryOp, op.value);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
    }

    return node;
}

std::shared_ptr<ASTNode> Parser::parseTerm()
{
    auto node = parseFactor();

    while (peek().type == TokenType::STAR || peek().type == TokenType::SLASH)
    {
        Token op = advance();
        auto right = parseFactor();
        auto newNode = std::make_shared<ASTNode>(ASTNodeType::BinaryOp, op.value);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parseFactor()
{
    if (peek().type == TokenType::NUMBER)
    {
        auto n = peek();

        advance(); // consume number
        return std::make_shared<ASTNode>(ASTNodeType::Number, n.value);
    }
    else if (peek().type == TokenType::WORD)
    {
        auto w = peek();
        advance(); // consume word
        auto node = std::make_shared<ASTNode>(ASTNodeType::Word, w.value);

        // parse the next expression as the left child (for function calls)
        auto next = parseExpression();
        next->left = node;
        return next;
    }
    else if (peek().type == TokenType::LPAREN)
    {
        advance();
        auto node = parseExpression();
        if (peek().type != TokenType::RPAREN)
        {
            throw std::runtime_error("Missing closing parenthesis");
        }
        advance(); // consume ')'
        return node;
    }
    throw std::runtime_error("Unexpected token: " + peek().value);
}
