#include "Token.h"
#include <iostream>

// Allow for tokens to be output to streams
std::ostream& operator<<(std::ostream& out, const Token& tok)
{
    out << "Token(" << tok.typeName();
    out << ", " << tok.valueName() << ")";
    return out;
}

std::string Token::TypeString(Type t)
{
    switch(t) {
        case (CTRL):
            return "CONTROL";
        case (OP):
            return "OPERATION";
        case (INT):
            return "INTEGER";
        case (REG):
            return "REGISTER";
        default:
            return "ERROR";
    }
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
    "PRINTD", // Print the contents of the register (dec)
    "PRINTX", // Print the contents of the register (hex)
    "PRINTC", // Print the contents of the register (char)
};

Op_Token::Op_Token(Op_Token::Op val): Token(val)
{
    switch(val)
    {
        case(ADD):
        case(SUB):
            opArgs = 3;
            immArg = false;
            break;

        case(ADDI):
            opArgs = 3;
            immArg = true;
            break;

        case(PRINTD):
            opArgs = 1;
            immArg = false;
            break;

        case(LI):
            opArgs = 2;
            immArg = true;
            break;

        default:
            opArgs = 0;
            immArg = false;
    }
}

std::string Op_Token::valueName() const
{
    return OpNames[this->getValue()];
}

//------------------Ctrl_Token Definitions---------------------

std::string Ctrl_Token::valueName() const
{
    switch(this->getValue())
    {
        case(END):
            return "END";
        case(SEP):
            return "SEPARATOR";
        default:
            return "ERROR";
    }
}
