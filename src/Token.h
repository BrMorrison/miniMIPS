#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

class Token
{
    // Operator delcaration
    friend std::ostream& operator<<(std::ostream&, const Token&);
    
    // public enumerated types    
    public:
    enum Type { // General token types
        CTRL,
        OP,
        INT,
        REG,
    };

    // public constructors and destructor
        Token() = default;
        Token(int val): value(val) { }

        virtual ~Token() = default;

    // public member functions
        static std::string TypeString(Type t);

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
        Token::Type getType() const override { return Token::INT; }
        std::string typeName() const override { return "INTEGER"; }
};

class Reg_Token: public Token
{
    public:
        Reg_Token(): Token() { }
        Reg_Token(int val): Token(val) { }

    // public member functions
        Token::Type getType() const override { return Token::REG; }
        std::string typeName() const override { return "REGISTER"; }
};

class Op_Token : public Token
{
    public:

    // public enum
    enum Op {
        // Arithmetic operators
        ADD     = 0,    // Signed addition
        ADDU    = 1,   // Unsigned addition
        SUB     = 2,    // Signed subtraction
        SUBU    = 3,   // Unsigned subtraction
        ADDI    = 4,   // Signed immediate addition
        ADDIU   = 5,  // Unsigned immediate addition
        MULT    = 6,   // Signed multiplication
        MULTU   = 7,  // Unsigned multiplication
        MFHI    = 8,   // Move from HI
        MFLO    = 9,   // Move from LO

        // Bitwise logic operators
        AND     = 10,    // Bitwise AND
        ANDI    = 11,   // Bitwise AND with immediate
        OR      = 12,     // Bitwise OR
        ORI     = 13,    // Bitwise OR with immediate
        XOR     = 14,    // Bitwise XOR
        XORI    = 15,   // Bitwise XOR with immediate
        NOR     = 16,    // Bitwise NOR

        // Don't know what to call these operator
        SLT     = 17,    // Set on less than
        SLTU    = 18,   // Unsigned Set on less than
        SLTI    = 19,   // Set on less than immediate

        // Bit-shift operations
        SLL     = 20,    // Logical shift left by immediate
        SRL     = 21,    // Logical shift right by immediate
        SRA     = 22,    // Arithmetic shift right by immediate
        SLLV    = 23,   // Logical shift left by register
        SRLV    = 24,   // Logical shift right by register
        SRAV    = 25,   // Arithmetic shift right by register

        // Pseudo operations
        MOVE    = 26,   // Move value between registers
        CLEAR   = 27,  // Clear register to zero
        NOT     = 28,    // Bit flip the register
        LI      = 29,     // Load immediate into register
        PRINTD  = 30, // Print the contents of the register (dec)
        PRINTX  = 32, // Print the contents of the register (hex)
        PRINTC  = 33, // Print the contents of the register (char)
    };
    
    // public constructors
        Op_Token(): Token() { }
        Op_Token(Op val);

    // public member functions
        Token::Type getType() const override { return Token::OP; }
        std::string typeName() const override { return "OPERATION"; }
        std::string valueName() const override;
        
        // Op_Token getters
        unsigned getNumArgs() const { return opArgs; }
        bool hasImm() const { return immArg; }

        static const std::vector<std::string> &GetOpNames() { return OpNames; }

    private:
    // private vector of ops
        static const std::vector<std::string> OpNames;
        unsigned opArgs;
        bool immArg;
};

class Ctrl_Token : public Token
{
    // public enum
    public:
    enum Ctrl {
        END,
        SEP,
    };

    // public constructors
        Ctrl_Token(): Token() { }
        Ctrl_Token(Ctrl val): Token((int)val) { }

    // public member functions
        Token::Type getType() const override { return Token::CTRL; }
        std::string typeName() const override { return "CONTROL"; }
        std::string valueName() const override;
};

#endif
