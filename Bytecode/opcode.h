#pragma once
#include <string>

enum class OpCode
{
    PUSH,  // push a number onto stack
    ADD,   // add top 2 values
    SUB,   // subtract top 2 values
    MUL,   // multiply top 2 values
    DIV,   // divide top 2 values
    PRINT, // print top of stack
    STORE,
    LOAD,
};

struct Instruction
{
    OpCode op;
    std::string operand; // used only for PUSH (the number as string)
};
