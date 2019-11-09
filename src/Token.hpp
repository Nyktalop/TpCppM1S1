#ifndef TPCPPM1S1_TOKEN_H
#define TPCPPM1S1_TOKEN_H

#include <vector>
#include <memory>


enum TokenType {
    NONE,
    NUMBER,
    CHAR
};


class ExprToken {
private:
    TokenType _type;

public:
    explicit ExprToken(TokenType type = NONE);

    inline const TokenType type() const { return _type; }

    bool operator<(const ExprToken &t) {
        return false;
    }

    virtual const double number() = 0;

    virtual const char character() = 0;
};

using vecToken = std::vector<std::unique_ptr<ExprToken>>;

class ExprTokenNumber : public ExprToken {
private :
    double _number;
public :
    explicit ExprTokenNumber(double i);

    inline const double number() override { return _number; }

    inline const char character() override { return 'o'; }


};

class ExprTokenChar : public ExprToken {
private :
    char _char;

public :
    explicit ExprTokenChar(char c);

    const char character() override { return _char; }

    const double number() override { return 0; }

    bool operator<(ExprToken &t) {
        if (t.type() != CHAR)
            return false;

        return (_char == '+' || _char == '-') && (t.character() == '*' || t.character() == '/');
    }
};


#endif //TPCPPM1S1_TOKEN_H
