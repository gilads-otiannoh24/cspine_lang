#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer/tokenizer.h"
#include "AST/ast.h"
#include "VM/vm.h"
#include "Bytecode/byte.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: cspine <file.cspine>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Could not open file: " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    try
    {
        auto tokens = tokenize(source);

        Parser parser(tokens);
        auto ast = parser.parse();

        BytecodeGenerator gen;
        auto bytecode = gen.generate(ast);

        auto node = ast; // for debugging
        bool leftDone = false;
        std::shared_ptr<ASTNode> currentLevel;
        auto first = true;

        while (node)
        {
            std::cout << "Node Type: " << static_cast<int>(node->type) << ", Value: " << node->value << "\n";

            node = node->left;
        }

        Interpreter vm;
        vm.run(bytecode);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
