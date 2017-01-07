#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TOKEN_TYPE_E {
    END,
    PLUS,
    INTEGER
};

class Token
{
    // public constructors
    public:
        Token() = default;
        Token(TOKEN_TYPE_E tt): type(tt) { value = -1; }
        Token(TOKEN_TYPE_E tt, int val): type(tt), value(val) { }

    // public member functions
    public:
        int getValue() const { return value; }
        TOKEN_TYPE_E getType() const { return type; }
        Token& operator=(const Token& rhs) {type = rhs.type; value = rhs.value; return *this;}

    private:
        TOKEN_TYPE_E type;
        int value;
};
#endif
