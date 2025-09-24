#pragma once
#include <memory>
#include "../Utils/keywords.h"

enum class ASTNodeType
{
    Number,
    BinaryOp,
    Word,
    EndOfLine,
    EndOfFile,
};

struct ASTNode
{
    ASTNodeType type;
    std::string value;   // numbers, operators, identifiers
    KeywordType keyword; // NONE if not a keyword
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;

    ASTNode(ASTNodeType t, std::string v, KeywordType k = KeywordType::NONE)
        : type(t), value(std::move(v)), keyword(k), left(nullptr), right(nullptr) {}
};
