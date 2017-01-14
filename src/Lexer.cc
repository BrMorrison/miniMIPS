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
    if(input->eof() || currentChar == ';')
    {
        return new Ctrl_Token(Ctrl_Token::END);
    }

    // See if we've encountered a separator
    else if(currentChar == ',')
    {
        *input >> currentChar;
        currentChar = input->peek();
        return new Ctrl_Token(Ctrl_Token::SEP);
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

    // See if we've encountered a negative number
    else if(currentChar == '-')
    {
        *input >> currentChar;
        currentChar = input->peek();

        // see if the minus was followed by an digit indicating
        // a negative number
        if(isdigit(currentChar))
        {
            int tmp;
            *input >> tmp;
            currentChar = input->peek();
            return new Int_Token(-1*tmp);
        }

        // If it wasn't part of a negative, throw an error
        else
        {
            std::ostringstream oss;
            oss << "Unexpected character encountered: " << currentChar;
            oss << "Expected a digit after '-' but encountered '"
                << currentChar << "' instead.";
            throw std::runtime_error(oss.str());
        }
    }

    // See if we've encountered a register
    else if(currentChar == '$')
    {
        // skip the '$' to get to the register number
        *input >> currentChar;
        currentChar = input->peek();

        // See if it's a number
        if(isdigit(currentChar))
        {
            int tmp;
            *input >> tmp;
            currentChar = input->peek();
            return new Reg_Token(tmp);
        }

        // TODO: add 'else if' statements or a switch statement to 
        // deal with alternative register names.

        else
        {
            std::ostringstream oss;
            oss << "Unexpected character encountered: " << currentChar;
            oss << "Expected a digit after '$' but encountered '"
                << currentChar << "' instead.";
            throw std::runtime_error(oss.str());
        }

    }

    // If all else fails, assume it's an opcode
    else
    {
        std::string tmp;
        *input >> tmp;

        currentChar = input->peek();

        return new Op_Token(tmp);
    }
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
