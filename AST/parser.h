#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../Lexer/token.h"
#include "ast.h"

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);

    // Main entry point for parsing (builds the AST root)
    std::shared_ptr<ASTNode> parse();

    void show();

private:
    // Helper functions
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();

    // Utility for managing tokens
    const Token peek() const;
    const Token advance();
    std::shared_ptr<ASTNode> parseWord(const Token &token);
    const Token consume(TokenType type, const std::string &message);
    const Token consume(const std::vector<TokenType> &types, const std::string &message);

    // Parser state
    std::vector<Token> tokens;
    size_t pos;
    std::shared_ptr<ASTNode> root;
};
