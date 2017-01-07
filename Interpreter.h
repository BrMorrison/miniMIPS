#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "Token.h"

// Create the Interpeter Class
class Interpreter {

    // public constructors
    public:
        Interpreter(const std::string &str) { text = new std::istringstream(str); }

    // public member functions
    public:
        int expr();

    // private member functions
    private:
        Token *getNextToken();
        void eat(const TOKEN_TYPE_E &token_type);

    // private instance variables
        std::istringstream *text;
        Token *currentToken;
};

void Interpreter::eat(const TOKEN_TYPE_E &token_type)
{
    if (currentToken->getType() == token_type)
    {
        // clean up the old token
        delete currentToken;

        // get the new token
        currentToken = this->getNextToken();
    }
    
    else
    {
        throw std::runtime_error("Unexpected token encountered");
    }
}

Token *Interpreter::getNextToken()
{
    // Check to see if we've his the EOF
    if(text->eof())
    {
        return new Token(END);
    }

    // If we're not at the end, grab a character.
    char c;
    text->get(c);

    // See if the character is a digit
    if(isdigit(c))
    {
        return new Token(INTEGER, c-'0');
    }

    // See if the character is a '+'
    else if(c == '+')
    {
        return new Token(PLUS);
    }

    // It wasn't a characer we support, so throw an error
    else
    {
        throw std::runtime_error("Unexpected character encountered");
    }
}

int Interpreter::expr()
{
    Token left, op, right;
    currentToken = this->getNextToken();

    // Get the left side of the expression
    left  = *currentToken;
    this->eat(INTEGER);

    // Get the operation
    op = *currentToken;
    this->eat(PLUS);

    // Get the right side of the expression
    right = *currentToken;
    this->eat(INTEGER);

    return (left.getValue() + right.getValue());
}

#endif
