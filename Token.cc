#include "Token.h"
#include <iostream>
#include <string>

// Convert the ENUMS to strings
std::string Token::TypeName(TOKEN_TYPE_E type) 
{
    switch(type) {
        case INTEGER:
            return "INTEGER";

        case PLUS:
            return "PLUS";

        case MINUS:
            return "MINUX";

        case END:
            return "END";

        // TODO: Make this throw an error
        default:
            return "ERROR";
    }
}

std::ostream& operator<<(std::ostream& out, const Token& tok)
{
    out << "Token(" << Token::TypeName(tok.type);
    if(tok.getValue() != -1)
    {
        out << ", " << tok.value;
    }
    out << ")";
    return out;
}

Token& Token::operator=(const Token& rhs)
{
    type = rhs.type; 
    value = rhs.value; 
    return *this;
}
