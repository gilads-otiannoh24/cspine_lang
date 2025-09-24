#include "../Lexer/token.h"
#include "../Utils/keywords.h"
#include "ast.h"
#include "parser.h"
#include <stdexcept>
#include <iostream>
#include <functional>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

std::shared_ptr<ASTNode> Parser::parse()
{
    root = parseExpression();

    /* You can perform any after tasks here */

    return root;
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
        return parseWord(peek());
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

    else if (peek().type == TokenType::LINE_END || peek().type == TokenType::SEMICOLON)
    {
        auto n = peek();
        advance(); // consume
        return std::make_shared<ASTNode>(ASTNodeType::EndOfLine, n.value);
    }

    else if (peek().type == TokenType::END_OF_FILE)
    {
        auto n = peek();
        advance(); // consume
        return std::make_shared<ASTNode>(ASTNodeType::EndOfFile, n.value);
    }

    throw std::runtime_error("Unexpected token: " + peek().value);
}

std::shared_ptr<ASTNode> Parser::parseWord(const Token &token)
{
    auto kw = lookupKeyword(token.value);

    if (kw == KeywordType::PRINT)
    {
        advance();
        // expect LPAREN <expr> RPAREN
        consume(TokenType::LPAREN, "Expected '(' after print");
        auto expr = parseExpression();
        // consume(TokenType::RPAREN, "Expected ')' after expression");

        auto node = std::make_shared<ASTNode>(ASTNodeType::Word, token.value, kw);
        node->left = expr; // attach the expression as child
        return node;
    }
    else if (kw == KeywordType::FN)
    {
        auto node = std::make_shared<ASTNode>(ASTNodeType::Word, advance().value, kw);
        // expect word (function name)
        auto name = consume(TokenType::WORD, "Expected function name after 'fn'");
        auto nameNode = std::make_shared<ASTNode>(ASTNodeType::Word, name.value);

        // expect LPAREN
        consume(TokenType::LPAREN, "Expected '(' after function name");

        // parse parameters (comma-separated words)
        std::shared_ptr<ASTNode> paramList = nullptr;
        std::shared_ptr<ASTNode> lastParam = nullptr;

        while (peek().type != TokenType::RPAREN && peek().type != TokenType::END_OF_FILE)
        {
            auto paramToken = consume(TokenType::WORD, "Expected parameter name");
            auto paramNode = std::make_shared<ASTNode>(ASTNodeType::Word, paramToken.value);

            if (!paramList)
            {
                paramList = paramNode;
            }
            else
            {
                lastParam->right = paramNode; // link parameters in a list
            }
            lastParam = paramNode;

            if (peek().type == TokenType::COMMA)
            {
                advance(); // consume comma
            }
            else
            {
                break; // no more parameters
            }
        }

        consume(TokenType::RPAREN, "Expected ')' after parameters");

        // Attach function name and parameters to the function node
        node->left = nameNode;
        node->right = paramList;

        return node;
    }
    else if (kw == KeywordType::LET)
    {
        auto node = std::make_shared<ASTNode>(ASTNodeType::Word, advance().value, kw);

        // expect word
        auto word = consume(TokenType::WORD, "Expected a variable name");
        auto varName = std::make_shared<ASTNode>(ASTNodeType::Word, token.value);

        // validate name
        if (lookupKeyword(word.value) != KeywordType::NONE)
            throw std::runtime_error("Invalid variable name: " + word.value);

        // expect assign
        consume(TokenType::STORE, "Expected '=' operator");

        // value number or word
        auto value = consume({TokenType::WORD, TokenType::NUMBER, TokenType::LINE_END, TokenType::SEMICOLON}, "Expected '=' operator");
        auto valueNode = std::make_shared<ASTNode>(ASTNodeType::Word, value.value);

        // return
        node->left = varName;
        node->right = valueNode;

        return node;
    }

    advance();

    // fallback: it's just a variable or function identifier
    return std::make_shared<ASTNode>(ASTNodeType::Word, token.value, kw);
}

const Token Parser::consume(TokenType type, const std::string &message)
{
    return consume(std::vector<TokenType>{type}, message);
}

const Token Parser::consume(const std::vector<TokenType> &types, const std::string &message)
{
    if (pos < tokens.size())
    {
        for (auto t : types)
        {
            if (tokens[pos].type == t)
            {
                return advance();
            }
        }
    }

    throw std::runtime_error("Parser Error: " + message +
                             ", got token: " + (pos < tokens.size() ? tokens[pos].value : "EOF"));
}

void Parser::show()
{
    std::function<void(const std::shared_ptr<ASTNode> &, int)> printNode;
    printNode = [&](const std::shared_ptr<ASTNode> &node, int depth)
    {
        if (!node)
            return;

        printNode(node->right, depth + 1);

        // Build node label: type + value (+ keyword if any)
        std::string typeStr;
        switch (node->type)
        {
        case ASTNodeType::Number:
            typeStr = "Number";
            break;
        case ASTNodeType::BinaryOp:
            typeStr = "BinaryOp";
            break;
        case ASTNodeType::Word:
            typeStr = "Word";
            break;
        }

        std::string kwStr;
        if (node->keyword != KeywordType::NONE)
        {
            switch (node->keyword)
            {
            case KeywordType::PRINT:
                kwStr = " [PRINT]";
                break;
            case KeywordType::LET:
                kwStr = " [LET]";
                break;
            case KeywordType::FN:
                kwStr = " [FN]";
                break;
            default:
                break;
            }
        }

        std::cout << std::string(depth * 4, ' ')
                  << typeStr << "(" << node->value << ")" << kwStr
                  << "\n";

        printNode(node->left, depth + 1);
    };

    printNode(root, 0);
}
