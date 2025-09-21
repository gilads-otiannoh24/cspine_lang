#include "../AST/ast.h"
#include "vm.h"
#include <stdexcept>

int VM::eval(const std::shared_ptr<ASTNode> &node)
{
    if (node->type == ASTNodeType::Number)
    {
        return std::stoi(node->value);
    }
    else if (node->type == ASTNodeType::BinaryOp)
    {
        int leftVal = eval(node->left);
        int rightVal = eval(node->right);

        if (node->value == "+")
            return leftVal + rightVal;
        if (node->value == "-")
            return leftVal - rightVal;
        if (node->value == "*")
            return leftVal * rightVal;
        if (node->value == "/")
            return leftVal / rightVal;

        throw std::runtime_error("Unknown operator: " + node->value);
    }
    throw std::runtime_error("Invalid AST Node");
}
