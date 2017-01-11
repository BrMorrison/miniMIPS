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
        default:
            return "ERROR";
    }
}


//--------------------Op_Token Definitions--------------------

std::string Op_Token::valueName() const
{
    switch(this->getValue())
    {
        case(PLUS):
            return "+";
        case(MINUS):
            return "-";
        case(TIMES):
            return "*";
        default:
            return "ERROR";
    }
}

//------------------Ctrl_Token Definitions---------------------

std::string Ctrl_Token::valueName() const
{
    switch(this->getValue())
    {
        case(END):
            return "END";
        default:
            return "ERROR";
    }
}
