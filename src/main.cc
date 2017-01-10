#include "Interpreter.h"

int main(int argc, char **argv)
{
    // Create a new interpreter that runs on stdin
    Interpreter interp = Interpreter();
    interp.run();
    return 0;
}
