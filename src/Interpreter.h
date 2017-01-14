#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <cstdint>
#include "Lexer.h"

// Interpeter Class
class Interpreter {

    // public constructors
    public:
        Interpreter();

    // public member functions
        void run();

    // private member functions
    private:
        int exec(const std::string &);
        void eat(Token::Type, Token *);
        void eat(Token::Type, int, Token *);

    // private instance variables
        // An array for the 32 general and 
        // special registers
        std::array<uint32_t, 34> regs;

        // An istream for input. Will allow me to
        // move away from stdin in the future.
        std::istream *text;
};

#endif
