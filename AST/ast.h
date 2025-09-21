#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../Lexer/token.h"

enum class ASTNodeType
{
    Number,
    BinaryOp
};

struct ASTNode
{
    ASTNodeType type;
    std::string value; // for numbers or operators
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    ASTNode(ASTNodeType t, std::string v)
        : type(t), value(std::move(v)), left(nullptr), right(nullptr) {}
};

class Parser
{
public:
    // Constructor takes a list of tokens
    Parser(const std::vector<Token> &tokens);

    // Main entry point for parsing (builds the AST root)
    std::shared_ptr<ASTNode> parse();

private:
    // Helper functions
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();

    // Utility for managing tokens
    const Token peek() const;
    const Token advance();

    // Parser state
    std::vector<Token> tokens;
    size_t pos;
};
