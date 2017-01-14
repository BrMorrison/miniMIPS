#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include "Token.h"

class Lexer
{
public:
    // The lexer does not have a default constructor because it
    // needs something to lex.
    Lexer();
    Lexer(const std::string &str);

    // The only thing we need to clean up in the deconstructor
    // string stream we create for the input.
    ~Lexer();

    // Produces a vector of Tokens generated from the string in the
    // order that they were encountered
    const std::vector<Token*> &getTokens();

private:
    // Gets a pointer to the next token from the string
    Token *getNextToken();

    std::vector<Token*> tokens;
    std::istringstream *input;
    char currentChar;
};

#endif
