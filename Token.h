#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TOKEN_TYPE_E {
    END,
    PLUS,
    MINUS,
    INTEGER
};

class Token
{
    // Operator delcarations
        friend std::ostream& operator<<(std::ostream&, const Token&);
    
    // public constructors
    public:
        Token() = default;
        Token(TOKEN_TYPE_E tt): type(tt) { value = -1; }
        Token(TOKEN_TYPE_E tt, int val): type(tt), value(val) { }

    // public member functions
    public:
        static std::string TypeName(TOKEN_TYPE_E);
        int getValue() const { return value; }
        TOKEN_TYPE_E getType() const { return type; }
        Token& operator=(const Token&);

    private:
        TOKEN_TYPE_E type;
        int value;
};

#endif
