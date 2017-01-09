#include "Token.h"
#include <iostream>

// Convert the ENUMS to strings
std::string Token::TypeName(Token::TYPE type) 
{
    // This is a very C-esque function and I might replace it with a map
    switch(type) {
        case Token::TYPE_INTEGER:
            return "INTEGER";

        case Token::TYPE_OPERATION:
            return "OPERATION";

        case Token::TYPE_END:
            return "END";

        // TODO: Make this throw an error
        default:
            return "ERROR";
    }
}

// Allow for tokens to be output to streams
std::ostream& operator<<(std::ostream& out, const Token& tok)
{
    // TODO: Modify this to work with the new operation tokens
    out << "Token(" << Token::TypeName(tok.type);
    if(tok.getValue() != -1)
    {
        out << ", " << tok.value;
    }
    out << ")";
    return out;
}

// Allow for copy assignment of Tokens
Token& Token::operator=(const Token& rhs)
{
    type = rhs.type; 
    value = rhs.value; 
    return *this;
}
