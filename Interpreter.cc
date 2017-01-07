#include "Interpreter.h"
#include <iostream>

int main(int argc, char **argv)
{
    Interpreter expression = Interpreter("3+5");
    std::cout << expression.expr() << std::endl;
    return 0;
}
