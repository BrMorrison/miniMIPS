#include "Interpreter.h"
#include <iostream>

// Check that the current token is valid and obtain the next one
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
        //TODO: Modify this to provide more information
        std::cout << "Encountered: " << *currentToken << std::endl;
        std::cout << "Expected: " << Token::TypeName(token_type) << std::endl;
        std::cout.flush();
        throw std::runtime_error("Unexpected token encountered");
    }
}

// Parse the next token from the text
Token *Interpreter::getNextToken()
{
    // Check to see if we've his the EOF
    if(text->eof())
    {
        return new Token(END);
    }

    else if(isspace(currentChar))
    {
        *text >> std::ws;
        currentChar = text->peek();
        return this->getNextToken();
    }

    // See if the character is a digit
    else if(isdigit(currentChar))
    {
        int tmp;
        *text >> tmp;
        currentChar = text->peek();
        return new Token(INTEGER, tmp);
    }

    // See if the character is a '+'
    else if(currentChar == '+')
    {
        *text >> currentChar;
        currentChar = text->peek();
        return new Token(PLUS);
    }

    // It wasn't a characer we support, so throw an error
    else
    {
        // TODO: Modify this to provide more information
        throw std::runtime_error("Unexpected character encountered");
    }
}

// Evaluate the expression
int Interpreter::expr()
{
    Token left, op, right;
    currentChar = text->peek();
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

    delete this->currentToken;

    return (left.getValue() + right.getValue());
}

int main(int argc, char **argv)
{
    std::string input;
    std::cout << "Calc>";
    std::getline (std::cin, input);
    while (input != "quit")
    {
        //TODO: Put this in a try/catch block
        Interpreter express = Interpreter(input);
        std::cout << express.expr() << std::endl;

        std::cout << "Calc>";
        std::getline (std::cin, input);
    }
    return 0;
}
