#include "Lexer.h"

// The primary constructor
Lexer::Lexer(const std::string &str)
{ 
    // create a string stream for the input
    input = new std::istringstream(str);
    currentChar = input->peek();
}

// Parse the next token from the input
Token Lexer::getNextToken()
{
    // Check to see if we've his the EOF
    // and if so, return an END token
    if(input->eof())
    {
        return Token(Token::TYPE_END);
    }

    // See if we're at some whitespace...
    else if(isspace(currentChar))
    {
        // ...if we are then go to the next interesting
        // character and call this function again.
        *input >> std::ws;
        currentChar = input->peek();
        return this->getNextToken();
    }

    // See if the character is a digit
    else if(isdigit(currentChar))
    {
        int tmp;
        // If we encountered a digit then use the stream
        // to parse it for us.
        *input >> tmp;
        currentChar = input->peek();
        return Token(Token::TYPE_INTEGER, tmp);
    }

    // See if the character is a '+'
    else if(currentChar == '+')
    {
        *input >> currentChar;
        currentChar = input->peek();
        return Token(Token::TYPE_OPERATION, Token::OPS_PLUS);
    }

    // It wasn't a characer we support, so throw an error
    else
    {
        // TODO: Modify this to provide more information
        std::ostringstream oss;
        oss << "Unexpected character encountered: " << currentChar;
        throw std::runtime_error(oss.str());
    }
    return Token(Token::TYPE_END);
}

// Take the provided string and obtain all the tokens we can
const std::vector<Token> &Lexer::getTokens()
{
    Token tmp = this->getNextToken();
    while(tmp.getType() != Token::TYPE_END)
    {
        // When we get a token push it onto the vector
        tokens.push_back(tmp);
        tmp = this->getNextToken();
    }
    return tokens;
}
