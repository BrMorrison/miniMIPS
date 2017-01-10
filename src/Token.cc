#include "Token.h"
#include <iostream>

// Allow for tokens to be output to streams
std::ostream& operator<<(std::ostream& out, const Token& tok)
{
    // TODO: Modify this to work with the new operation tokens
    out << "Token(" << tok.typeName();
    out << ", " << tok.valueName() << ")";
    return out;
}


//--------------------Op_Token Definitions--------------------

std::string Op_Token::valueName() const
{
    switch(this->getValue())
    {
        case(Op_Token::PLUS):
            return "+";
        case(Op_Token::MINUS):
            return "-";
        case(Op_Token::TIMES):
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
        case(Ctrl_Token::END):
            return "END";
        default:
            return "ERROR";
    }
}
