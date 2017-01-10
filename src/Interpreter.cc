#include "Interpreter.h"
#include <iostream>

// Default constructer
Interpreter::Interpreter()
{
    // The user did not specify a file so we're running off stdin
    prompt = true;
    text = &std::cin;
}

// Interpret code from a file
Interpreter::Interpreter(const std::string &str)
{ 
    // This isn't supported yet, which is why text is initialized as a nullptr
    prompt = false;
    text = nullptr;
}

// Performs a check to make sure that an expected token type was encountered.
// If the token encountered was not the expected type then a runtime error is thrown.
void Interpreter::eat(Token::Type token_type, Token *t)
{
    if (t->getType() != token_type)
    {
        // Use a string stream to create an informative error message.
        std::ostringstream oss;
        oss << "Unexpected token encountered: " << *t << std::endl;
        throw std::runtime_error(oss.str());
    }
    // If the token is the right kind, do nothing
}

// Executes a single line of code and returns the result.
//
// currently returns an int because all operations performed are arithmetic, but
// this will likely be changed to void when the code stops doing math and starts
// advancing the state of the program.
int Interpreter::exec(const std::string &line)
{
    // This whole function is terribly written and will be improved when the
    // interpreter has to start doing real work instead of simple math.
    
    // These are the tokens we will need for our math operation
    Token *left, *op, *right;

    // Take the line of code and send it to the lexer to get some tokens
    Lexer lex = Lexer(line);
    // Create an iterator on the vector returned by the lexer so that we can
    // iterate over the tokens.
    auto ct = lex.getTokens().begin();

    // Get the left side of the expression
    left  = *(ct++);
    this->eat(Token::INT, left);

    // Get the operation
    op = *(ct++);
    this->eat(Token::OP, op);

    // Get the right side of the expression
    right = *(ct++);
    this->eat(Token::INT, right);

    // Perform the arithmetic based on the value of op
    switch(op->getValue())
    {
        case(Op_Token::PLUS):
            return (left->getValue() + right->getValue());

        case(Op_Token::MINUS):
            return (left->getValue() - right->getValue());

        case(Op_Token::TIMES):
            return (left->getValue() * right->getValue());

        default:
            return -1;
    }
}

// Run the interpreter and keep going until we hit the end of file
// or the user asks to quit.
void Interpreter::run()
{
    std::string input;
    int tmp;

    // See if we need to print a prompt (probably means the interpreter
    // is running off stdin)
    if (prompt)
    {
        std::cout << std::endl;
        std::cout << "Welcome to what is currently a simple calculator!" << std::endl << std::endl
            << "To use it just enter a simple positive integer expression at the prompt." << std::endl
            << "For example, you can enter something like \"2+3\" or \"12 * 7\"." << std::endl
            << "The currently the following operations are supported:" << std::endl
            << "Addition, subtraction, and multiplication (but not division)" << std::endl;
        std::cout << "Type \"quit\" to exit" << std::endl << std::endl;
        std::cout << "Calc>";
    }

    std::getline(*text, input);
    
    while (!text->eof() && input != "quit")
    {
        // Try to execute the line of code
        try
        {
            tmp = this->exec(input);
        }
        
        // If we get an error, print the message and exit gracefully.
        catch (std::runtime_error err)
        {
            std::cerr << err.what() << std::endl;
            break;
        }
        
        // If the user needs a prompt then print it with the output
        if (prompt)
        {
            std::cout << tmp << std::endl << "Calc>";
        }

        // Get the next line of input
        std::getline(*text, input);
    }
}

