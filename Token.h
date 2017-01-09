#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
    // Operator delcarations
    friend std::ostream& operator<<(std::ostream&, const Token&);
    
    public:
    // Public enumerated types    

    // General token types
    enum TYPE {
        TYPE_END,
        TYPE_OPERATION,
        TYPE_INTEGER
    };

    // Different operations for OPERATION tokens
    enum OPS {
        OPS_PLUS,
        OPS_MINUS,
        OPS_TIMES,
        OPS_MOD
    };

    // public constructors
        Token() = default;
        Token(TYPE tt): type(tt) { value = 0; }
        Token(TYPE tt, OPS op): type(tt), value(op) { }
        Token(TYPE tt, int val): type(tt), value(val) { }

    // public member functions
    public:
        static std::string TypeName(TYPE);
        int getValue() const { return value; }
        TYPE getType() const { return type; }
        Token& operator=(const Token&);

    private:
        TYPE type;
        int value;
};

#endif
