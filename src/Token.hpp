#ifndef TPCPPM1S1_TOKEN_H
#define TPCPPM1S1_TOKEN_H

#include <vector>
#include <memory>


enum TokenType {
	NONE,
	NUMBER,
	OP
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

	virtual const char op() = 0;
};

using vecToken = std::vector<std::unique_ptr<ExprToken>>;

class ExprTokenNumber : public ExprToken {
private :
	double _number;
public :
	explicit ExprTokenNumber(double i);

	inline const double number() override { return _number; }

	inline const char op() override { return 'o'; }


};

class ExprTokenOp : public ExprToken {
private :
	char _op;

public :
	explicit ExprTokenOp(char c);

	const char op() override { return _op; }

	const double number() override { return 0; }

	bool operator<(ExprToken &t) {
		if (t.type() != OP)
			return false;

		return (_op == '+' || _op == '-') && (t.op() == '*' || t.op() == '/');
	}
};


#endif //TPCPPM1S1_TOKEN_H
