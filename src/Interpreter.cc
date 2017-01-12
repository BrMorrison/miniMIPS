#include "Interpreter.h"
#include <iostream>

// Default constructer
Interpreter::Interpreter()
{
    // The user did not specify a file so we're running off stdin
    text = &std::cin;
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
        oss << "Expected token of type: " << Token::TypeString(token_type);
        throw std::runtime_error(oss.str());
    }
    // If the token is the right kind, do nothing
}

void Interpreter::eat(Token::Type token_type, int token_value, Token *t)
{
    // first make sure the type is right
    this->eat(token_type, t);

    // then see if the value is correct
    if (t->getValue() != token_value)
    {
        // Use a string stream to create an informative error message.
        std::ostringstream oss;
        oss << "Unexpected token encountered: " << *t << std::endl;
        oss << "Expected token of type '" << Token::TypeString(token_type);
        oss << "' and value '" << t->valueName() << "'";
        throw std::runtime_error(oss.str());
    }
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
    
    Token *tmp;

    Token::Type expected_tok = Token::OP;

    // a vector to hold the operands for the opcode
    std::vector<Token *> args;

    // Take the line of code and send it to the lexer to get some tokens
    Lexer lex(line);
    // Create an iterator on the vector returned by the lexer so that we can
    // iterate over the tokens.
    auto ct = lex.getTokens().begin();

    // Get the operation
    tmp = *(ct++);
    this->eat(expected_tok, tmp);

    // We've checked the type so this cast is safe
    Op_Token *op = dynamic_cast<Op_Token*>(tmp);

    // Every operation involves a register (expect for some jumps)
    // which will generally be followed by a comma
    expected_tok = Token::REG;
    Ctrl_Token::Ctrl expected_ctrl = Ctrl_Token::SEP;


    // Loop for collecting the operands for the instruction
    for(unsigned i = 0; i != op->getNumArgs(); ++i)
    {
        // If this is the last operand
        if(i == op->getNumArgs() - 1)
        {
            // This is the last one so we want an end token
            expected_ctrl = Ctrl_Token::END;
            
            // If the operation expects an immediate it will be the last operand
            if (op->hasImm())
            {
                expected_tok = Token::INT;
            }
        }

        // Get the next token
        tmp = *(ct++);
        this->eat(expected_tok, tmp);

        // Save the token for the execution of the instruction
        args.push_back(tmp);

        // Make sure that whatever control token we were expecting comes next
        this->eat(Token::CTRL, expected_ctrl, *(ct++));
    }


    // Perform the arithmetic based on the value of op
    int dest, val1, val2;
    switch(op->getValue())
    {
        case(Op_Token::ADD):
            dest = args[0]->getValue();
            val1 = args[1]->getValue();
            val2 = args[2]->getValue();

            registers[dest] = registers[val1] + registers[val2];
            return 0;

        case(Op_Token::PRINTD):
            val1 = args[0]->getValue();
            std::cout << registers[val1] << std::endl;
            return 0;

        case(Op_Token::LI):
            dest = args[0]->getValue();
            val1 = args[1]->getValue();
            registers[dest] = val1;
            return 0;

        default:
            return -1;
    }
}

// Run the interpreter and keep going until we hit the end of file
// or the user asks to quit.
void Interpreter::run()
{
    std::string input;

    std::cout << "Type \"quit\" to exit" << std::endl << std::endl;
    std::cout << "Calc>";

    std::getline(*text, input);
    
    while (!text->eof() && input != "quit")
    {
        if(input == "")
        {
            std::cout << "Calc>";
            std::getline(std::cin, input);
            continue;
        }

        // Try to execute the line of code
        try
        {
            this->exec(input);
        }
        
        // If we get an error, print the message and exit gracefully.
        catch (std::runtime_error err)
        {
            std::cerr << err.what() << std::endl;
            std::cout << "Calc>";
            std::getline(*text, input);
            continue;
        }
        
        // reprompt
        std::cout << "Calc>";

        // Get the next line of input
        std::getline(*text, input);
    }
}

