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
void Interpreter::eat(Token::TYPE token_type, const Token &t)
{
    if (t.getType() != token_type)
    {
        // Use a string stream to create an informative error message.
        std::ostringstream oss;
        oss << "Unexpected token encountered: " << t << std::endl;
        oss << "Expected a token of type: " << Token::TypeName(token_type);
        throw std::runtime_error(oss.str());
    }
    // Currently if the expected type is encountered then no actions are performed.
    // In the future this may be expanded to advance the code execution as well.
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
    Token left, op, right;

    // Take the line of code and send it to the lexer to get some tokens
    Lexer lex = Lexer(line);
    // Create an iterator on the vector returned by the lexer so that we can
    // iterate over the tokens.
    auto ct = lex.getTokens().begin();

    // Get the left side of the expression
    left  = *(ct++);
    this->eat(Token::TYPE_INTEGER, left);

    // Get the operation
    op = *(ct++);
    this->eat(Token::TYPE_OPERATION, op);

    // Get the right side of the expression
    right = *(ct++);
    this->eat(Token::TYPE_INTEGER, right);

    return (left.getValue() + right.getValue());
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

int main(int argc, char **argv)
{
    // Create a new interpreter that runs on stdin
    Interpreter interp = Interpreter();
    interp.run();
    return 0;
}
