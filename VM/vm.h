#pragma once
#include "../AST/ast.h"
#include "../AST/parser.h"
#include "../Bytecode/opcode.h"
#include <stack>
#include <vector>

class Evaluator
{
public:
    int eval(const std::shared_ptr<ASTNode> &node);
};

class Interpreter
{
public:
    void run(const std::vector<Instruction> &instructions);

private:
    int pop(std::stack<int> &s);
};
