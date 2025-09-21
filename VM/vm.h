#pragma once
#include "../AST/ast.h"

class VM
{
public:
    int eval(const std::shared_ptr<ASTNode> &node);
};
