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
        oss << "Expected token of type: " << Token::getTypeString(token_type);
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
        oss << "Expected token of type '" << Token::getTypeString(token_type);
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

    // a vector to hold the operands for the opcode
    std::vector<int> args;

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
        args.push_back(tmp->getValue());

        // Make sure that whatever control token we were expecting comes next
        this->eat(Token::CTRL, expected_ctrl, *(ct++));
    }

    // Make sure the zero regsiter is set to 0 before any operations are performed
    regs[0] = 0;

    // Perform the arithmetic based on the value of op
    switch(op->getValue())
    {
        //--------Arithmetic Operations----------

        // Register addition
        case(Op_Token::ADD):
        case(Op_Token::ADDU):
            regs[args[0]] = regs[args[1]] + regs[args[2]];
            return 0;
        // Immediate addition
        case(Op_Token::ADDI):
        case(Op_Token::ADDIU):
            regs[args[0]] = regs[args[1]] + args[2];
            return 0;
        // Subtraction
        case(Op_Token::SUB):
        case(Op_Token::SUBU):
            regs[args[0]] = regs[args[1]] - regs[args[2]];
            return 0;
        // Multiplication
        case(Op_Token::MULT):
        case(Op_Token::MULTU):
            // Set LO with the lower word of the result
            regs[30] = (((uint64_t)regs[args[0]] * (uint64_t)regs[args[1]]) << 32) >> 32;
            // Set HI with the upper word of the result
            regs[31] = ((uint64_t)regs[args[0]] * (uint64_t)regs[args[1]]) >> 32;
            return 0;

        // Move from special registers
        case(Op_Token::MFHI):
            regs[args[0]] = regs[31];
            return 0;
        case(Op_Token::MFLO):
            regs[args[0]] = regs[30];
            return 0;

        //----------Bitwise Operations-----------

        // Register AND
        case(Op_Token::AND):
            regs[args[0]] = regs[args[1]] & regs[args[2]];
            return 0;
        // Immediate AND
        case(Op_Token::ANDI):
            regs[args[0]] = regs[args[1]] & args[2];
            return 0;
        // Register OR
        case(Op_Token::OR):
            regs[args[0]] = regs[args[1]] | regs[args[2]];
            return 0;
        // Immediate OR
        case(Op_Token::ORI):
            regs[args[0]] = regs[args[1]] | args[2];
            return 0;
        // Register XOR
        case(Op_Token::XOR):
            regs[args[0]] = regs[args[1]] ^ regs[args[2]];
            return 0;
        // Immediate XOR
        case(Op_Token::XORI):
            regs[args[0]] = regs[args[1]] ^ args[2];
            return 0;
        // Register NOR
        case(Op_Token::NOR):
            regs[args[0]] = ~(regs[args[1]] | regs[args[2]]);
            return 0;

        //----------Logical Operations-----------

        // Set less than
        case(Op_Token::SLT):
            regs[args[0]] = ((int)regs[args[1]]) < ((int)regs[args[2]]);
            return 0;
        // Set less than unsigned
        case(Op_Token::SLTU):
            regs[args[0]] = ((unsigned)regs[args[1]]) < ((unsigned)regs[args[2]]);
            return 0;
        // Set less than immediate
        case(Op_Token::SLTI):
            regs[args[0]] = ((int)regs[args[1]]) < ((int)args[2]);
            return 0;
                
        //----------Shift Operations-----------

        // Immediate logical left shift
        case(Op_Token::SLL):
            regs[args[0]] = regs[args[1]] << args[2];
            return 0;
        // Immediate logical right shift
        case(Op_Token::SRL):
            regs[args[0]] = ((unsigned)regs[args[1]]) >> args[2];
            return 0;
        // Immediate arithmetic right shift
        case(Op_Token::SRA):
            regs[args[0]] = ((int)regs[args[1]]) >> args[2];
            return 0;
        // Logical left shift
        case(Op_Token::SLLV):
            regs[args[0]] = regs[args[1]] << regs[args[2]];
            return 0;
        // Logical right shift
        case(Op_Token::SRLV):
            regs[args[0]] = ((unsigned)regs[args[1]]) >> regs[args[2]];
            return 0;
        // Arithmetic right shift
        case(Op_Token::SRAV):
            regs[args[0]] = ((int)regs[args[1]]) >> regs[args[2]];
            return 0;

        //----------Psuedo Operations-----------

        // Move value
        case(Op_Token::MOVE):
            regs[args[0]] = regs[args[1]];
            return 0;
        // Clear register
        case(Op_Token::CLEAR):
            regs[args[0]] = 0;
            return 0;
        // Bitwise not
        case(Op_Token::NOT):
            regs[args[0]] = ~(regs[args[1]]);
            return 0;
        // Load immediate
        case(Op_Token::LI):
            regs[args[0]] = args[1];
            return 0;
        // print unsigned
        case(Op_Token::PRINTU):
            std::cout << (uint32_t)regs[args[0]] << std::endl;
            return 0;
        // print signed
        case(Op_Token::PRINTS):
            std::cout << (int32_t)regs[args[0]] << std::endl;
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

