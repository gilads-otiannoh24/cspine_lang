#include <iostream>
#include "Lexer/tokenizer.h"
#include "AST/builder.h"
#include "VM/vm.h"
#include "Bytecode/byte.h"
#include "Utils/types.h"

int main()
{
    std::cout << "Toy language running..." << std::endl;

    // Example usage
    tokenize("1 + 2");
    build_ast("1");
    parse_ast();
    run_vm();

    User u = {"ian", 1};
    cout << u.username << endl;

    return 0;
}
