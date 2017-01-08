#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstdlib>
#include "Token.h"

// Create the Interpeter Class
class Interpreter {

    // public constructors
    public:
        Interpreter(const std::string &str);

    // public member functions
    public:
        int expr();

    // private member functions
    private:
        Token *getNextToken();
        int parseInt();
        void skipSpace();
        void eat(const TOKEN_TYPE_E &token_type);
        void advance();

    // private instance variables
        std::unique_ptr<std::istream> text;
        Token *currentToken;
        char currentChar;
};

//TODO: Stop using a unique_ptr and make a deconstructor instead
Interpreter::Interpreter(const std::string &str)
{ 
    // Create a unique pointer for the string stream
    std::unique_ptr<std::istream> tmp(new std::istringstream(str)); 
    text = std::move(tmp);
}

#endif
