#include "Lexer.h"

// The default constructor
Lexer::Lexer()
{
    input = new std::istringstream("");
    currentChar = input->peek();
}

// The primary constructor
Lexer::Lexer(const std::string &str)
{ 
    // create a string stream for the input
    input = new std::istringstream(str);
    currentChar = input->peek();
}

Lexer::~Lexer()
{
    // clean up the stream
    delete input;
    
    // Go through the tokens we have and clean them up
    for(auto iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        delete *iter;
    }
}

// Parse the next token from the input
Token *Lexer::getNextToken()
{
    // Check to see if we've his the EOF
    // and if so, return an END token
    if(input->eof())
    {
        return new Ctrl_Token(Ctrl_Token::END);
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
        return new Int_Token(tmp);
    }

    else if(currentChar == '+')
    {
        // advance the stream
        *input >> currentChar;
        // get the next character
        currentChar = input->peek();
        // create an addition token
        return new Op_Token(Op_Token::PLUS);
    }

    else if(currentChar == '-')
    {
        // see the '+' description
        *input >> currentChar;
        currentChar = input->peek();
        return new Op_Token(Op_Token::MINUS);
    }

    else if(currentChar == '*')
    {
        // see the '+' description
        *input >> currentChar;
        currentChar = input->peek();
        return new Op_Token(Op_Token::TIMES);
    }

    // It wasn't a characer we support, so throw an error
    else
    {
        // TODO: Modify this to provide more information
        std::ostringstream oss;
        oss << "Unexpected character encountered: " << currentChar;
        throw std::runtime_error(oss.str());
    }
    return new Ctrl_Token(Ctrl_Token::END);
}

// Take the provided string and obtain all the tokens we can
const std::vector<Token*> &Lexer::getTokens()
{
    Token *tmp = this->getNextToken();
    while(!(tmp->getType() == Token::CTRL && tmp->getValue() == Ctrl_Token::END))
    {
        // When we get a token push it onto the vector
        tokens.push_back(tmp);
        tmp = this->getNextToken();
    }

    tokens.push_back(tmp);
    return tokens;
}
