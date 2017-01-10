#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <sstream>
#include <string>
#include "Lexer.h"

// Interpeter Class
class Interpreter {

    // public constructors
    public:
        Interpreter();
        Interpreter(const std::string &file);

    // public member functions
        void run();

    // private member functions
    private:
        int exec(const std::string &);
        void eat(Token::Type, Token *);

    // private instance variables
        std::istream *text;
        bool prompt;
};

#endif
