#include "../AST/ast.h"
#include "../Bytecode/opcode.h"
#include "vm.h"
#include <stdexcept>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

int Evaluator::eval(const std::shared_ptr<ASTNode> &node)
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

int Interpreter::pop(std::stack<int> &s)
{
    if (s.empty())
        throw std::runtime_error("Stack underflow!");
    auto val = s.top();
    s.pop();
    return val;
}

void Interpreter::run(const std::vector<Instruction> &instructions)
{
    std::stack<int> stack;

    for (const auto &instr : instructions)
    {
        switch (instr.op)
        {
        case OpCode::PUSH:
            stack.push(std::stoi(instr.operand));
            break;

        case OpCode::ADD:
        {
            int b = pop(stack);
            int a = pop(stack);
            stack.push(a + b);
            break;
        }
        case OpCode::SUB:
        {
            int b = pop(stack);
            int a = pop(stack);
            stack.push(a - b);
            break;
        }
        case OpCode::MUL:
        {
            int b = pop(stack);
            int a = pop(stack);
            stack.push(a * b);
            break;
        }
        case OpCode::DIV:
        {
            int b = pop(stack);
            int a = pop(stack);
            if (b == 0)
                throw std::runtime_error("Division by zero!");
            stack.push(a / b);
            break;
        }
        case OpCode::PRINT:
            if (!stack.empty())
            {
                std::cout << pop(stack) << std::endl;
            }
            else
            {
                throw std::runtime_error("Runtime Error: Nothing to print");
            }
            break;
        }
    }
}
