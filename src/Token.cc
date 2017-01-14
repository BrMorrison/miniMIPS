#include "Token.h"
#include <iostream>

// Allow for tokens to be output to streams
std::ostream& operator<<(std::ostream& out, const Token& tok)
{
    out << "Token(" << tok.typeName();
    out << ", " << tok.valueName() << ")";
    return out;
}

// A vector containing the names of the token types
const std::vector<std::string> Token::TypeNames = {
    "CONTROL",
    "OPERATION",
    "INTEGER",
    "REGISTER",
};

// Produces a string based on and enum type value
std::string Token::getTypeString(Type t)
{
    if (t >= TYPE_ERROR)
    {
        return "ERROR";
    }
    
    else
    {
        return TypeNames[t];
    }
}
//-------------------Reg_Token Definitions--------------------

// produces a register token for the provided register number
Reg_Token::Reg_Token(int val) : Token(val)
{
    // Make sure the val is a valid value for an register token
    if (val >= 32 || val < 0)
    {
        std::ostringstream oss;
        oss << "Invalid register value passed to Reg_Token constructor: "
            << val << std::endl << "Expected a value between 0 and 31";

        throw std::runtime_error(oss.str());
    }
}

// Returns the name of the register
std::string Reg_Token::valueName() const
{
    //TODO: revamp this to provide more specific register names
    std::ostringstream oss;
    oss << "Reg " << this->getValue();
    return oss.str();
}

//--------------------Op_Token Definitions--------------------

const std::vector<std::string> Op_Token::OpNames = {
    // Arithmetic operators
    "ADD",    // Signed addition
    "ADDU",   // Unsigned addition
    "SUB",    // Signed subtraction
    "SUBU",   // Unsigned subtraction
    "ADDI",   // Signed immediate addition
    "ADDIU",  // Unsigned immediate addition
    "MULT",   // Signed multiplication
    "MULTU",  // Unsigned multiplication
    "MFHI",   // Move from HI
    "MFLO",   // Move from LO

    // Bitwise logic operators
    "AND",    // Bitwise AND
    "ANDI",   // Bitwise AND with immediate
    "OR",     // Bitwise OR
    "ORI",    // Bitwise OR with immediate
    "XOR",    // Bitwise XOR
    "XORI",   // Bitwise XOR with immediate
    "NOR",    // Bitwise NOR

    // Don't know what to call these operator
    "SLT",    // Set on less than
    "SLTU",   // Unsigned Set on less than
    "SLTI",   // Set on less than immediate

    // Bit-shift operations
    "SLL",    // Logical shift left by immediate
    "SRL",    // Logical shift right by immediate
    "SRA",    // Arithmetic shift right by immediate
    "SLLV",   // Logical shift left by register
    "SRLV",   // Logical shift right by register
    "SRAV",   // Arithmetic shift right by register

    // Pseudo operations
    "MOVE",   // Move value between registers
    "CLEAR",  // Clear register to zero
    "NOT",    // Bit flip the register
    "LI",     // Load immediate into register
    "PRINTU", // Print the contents of the register unsigned
    "PRINTS", // Print the contents of the register signed
};

// Produces the name of the operation from an enum value
std::string Op_Token::getOpString(Op o)
{
    if (o >= OP_ERROR)
    {
        return "ERROR";
    }
    
    else
    {
        return OpNames[o];
    }
}

// returns the name of a token's value
std::string Op_Token::valueName() const
{
    return OpNames[this->getValue()];
}

// attempt to create an operation token based on an enum value
Op_Token::Op_Token(Op_Token::Op val): Token(val)
{
    // Make sure the val is a valid value for an op token
    if (val >= OP_ERROR || val < ADD)
    {
        std::ostringstream oss;
        oss << "Invalid operation value passed to Op_Token constructor: "
            << val << std::endl << "Expected a value between " << ADD
            << " and " << OP_ERROR-1;

        throw std::runtime_error(oss.str());
    }
    
    init();
}

// attempt to create an operation token based on an enum value
Op_Token::Op_Token(std::string const & str): Token()
{
    auto beg = OpNames.cbegin();
    auto end = OpNames.cend();
    // go through the list of names and see if it matches one
    for(auto iter = beg; iter != end; ++iter)
    {
        if(str == *iter)
        {
            int val = (iter-beg);
            this->setValue(val);
            init();
            return;
        }
    }
    // if there was no match, throw an error
    std::ostringstream oss;
    oss << "Invalid string passed to Op_Token constructor." << std::endl;
    oss << "'" << str << "' is not recognized as a valid opcode.";
    throw std::runtime_error(oss.str());
}

// initializes the op token based on what operation it represents
void Op_Token::init()
{

    // Assign the number of operands and the pressence of an immediate operand
    // based on each opcode
    switch(this->getValue())
    {
        case(ADD):
        case(ADDU):
        case(SUB):
        case(SUBU):
        case(AND):
        case(ANDI):
        case(OR):
        case(ORI):
        case(XOR):
        case(XORI):
        case(NOR):
        case(SLT):
        case(SLTU):
        case(SLLV):
        case(SRLV):
        case(SRAV):
            opArgs = 3;
            immArg = false;
            break;

        case(ADDI):
        case(ADDIU):
        case(SLTI):
        case(SLL):
        case(SRL):
        case(SRA):
            opArgs = 3;
            immArg = true;
            break;

        case(MULT):
        case(MULTU):
        case(MOVE):
        case(NOT):
            opArgs = 2;
            immArg = false;
            break;

        case(LI):
            opArgs = 2;
            immArg = true;
            break;

        case(MFHI):
        case(MFLO):
        case(CLEAR):
        case(PRINTU):
        case(PRINTS):
            opArgs = 1;
            immArg = false;
            break;

        default:
            opArgs = 0;
            immArg = false;
    }
}

//------------------Ctrl_Token Definitions---------------------

const std::vector<std::string> Ctrl_Token::CtrlNames = {
    "END",
    "SEPARATOR",
};

// Get the name of the control token from an enum value
std::string Ctrl_Token::getCtrlString(Ctrl c)
{
    if (c >= CTRL_ERROR)
    {
        return "ERROR";
    }
    
    else
    {
        return CtrlNames[c];
    }
}

std::string Ctrl_Token::valueName() const
{
    return CtrlNames[this->getValue()];
}

Ctrl_Token::Ctrl_Token(Ctrl_Token::Ctrl val): Token(val)
{
    // The constructor just checks to make sure val was valid for a ctrl token
    if (val >= CTRL_ERROR || val < END)
    {
        std::ostringstream oss;
        oss << "Invalid operation value passed to Ctrl_Token constructor: "
            << val << std::endl << "Expected a value between " << END
            << " and " << CTRL_ERROR-1;

        throw std::runtime_error(oss.str());
    }
}
