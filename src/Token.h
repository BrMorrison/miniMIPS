#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
    // Operator delcaration
    friend std::ostream& operator<<(std::ostream&, const Token&);
    
    // public enumerated types    
    public:
    enum Type { // General token types
        CTRL,
        OP,
        INT
    };

    // public constructors and destructor
    public:
        Token() = default;
        Token(int val): value(val) { }

        virtual ~Token() = default;

    // public member functions
    public:
        int getValue() const { return value; }
        virtual std::string valueName() const { return std::to_string(value); }
        virtual Type getType() const = 0;
        virtual std::string typeName() const = 0;

    // private instance variables
    private:
        int value;
};

class Int_Token : public Token
{
    // public constructors
    public:
        Int_Token(): Token() { }
        Int_Token(int val): Token(val) { }

    // public member functions
    public:
        Token::Type getType() const override { return Token::INT; }
        std::string typeName() const override { return "INTEGER"; }
};

class Op_Token : public Token
{
    // public enum
    public:
    enum Op {
        PLUS,
        MINUS,
        TIMES
    };

    // public constructors
    public:
        Op_Token(): Token() { }
        Op_Token(Op val): Token((int)val) { }

    // public member functions
    public:
        Token::Type getType() const override { return Token::OP; }
        std::string typeName() const override { return "OPERATION"; }
        std::string valueName() const override;
};

class Ctrl_Token : public Token
{
    // public enum
    public:
    enum Ctrl {
        END
    };

    // public constructors
    public:
        Ctrl_Token(): Token() { }
        Ctrl_Token(Ctrl val): Token((int)val) { }

    // public member functions
    public:
        Token::Type getType() const override { return Token::CTRL; }
        std::string typeName() const override { return "CONTROL"; }
        std::string valueName() const override;
};
#endif
