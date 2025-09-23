#pragma once

#include <vector>
#include <memory>
#include <string>
#include "opcode.h"
#include "../AST/ast.h"

class BytecodeGenerator
{
public:
    std::vector<Instruction> generate(const std::shared_ptr<ASTNode> &node);

private:
    std::vector<Instruction> instructions;

    void emitNode(const std::shared_ptr<ASTNode> &node);
};
