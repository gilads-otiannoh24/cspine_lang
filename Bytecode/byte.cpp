#include <vector>
#include <memory>
#include <string>
#include "../AST/ast.h"
#include "byte.h"
#include "opcode.h"
#include "../Utils/keywords.h"

std::vector<Instruction> BytecodeGenerator::generate(const std::shared_ptr<ASTNode> &node)
{
    instructions.clear();
    emitNode(node);
    return instructions;
}

void BytecodeGenerator::emitNode(const std::shared_ptr<ASTNode> &node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case ASTNodeType::Number:
        instructions.push_back({OpCode::PUSH, node->value});
        break;

    case ASTNodeType::BinaryOp:
        emitNode(node->left);  // evaluate left side
        emitNode(node->right); // evaluate right side

        if (node->value == "+")
            instructions.push_back({OpCode::ADD, ""});
        else if (node->value == "-")
            instructions.push_back({OpCode::SUB, ""});
        else if (node->value == "*")
            instructions.push_back({OpCode::MUL, ""});
        else if (node->value == "/")
            instructions.push_back({OpCode::DIV, ""});
        break;
    case ASTNodeType::Word:
        emitNode(node->left);  // evaluate left side
        emitNode(node->right); // evaluate right side

        // check for keywords like "print" or "let"
        if (lookupKeyword(node->value) == KeywordType::PRINT)
            instructions.push_back({OpCode::PRINT, ""});
        else if (lookupKeyword(node->value) == KeywordType::LET)
            ; // handle variable declaration (not implemented)
        else if (lookupKeyword(node->value) == KeywordType::FN)
            ; // handle variable declaration (not implemented)
        else
            ; // handle variable usage (not implemented)
        break;
    }
}
