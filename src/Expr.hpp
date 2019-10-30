#ifndef TPCPPM1S1_EXPR_H
#define TPCPPM1S1_EXPR_H

#include <vector>
#include <memory>
#include <cmath>

#include "Token.hpp"

using vecToken = std::vector<std::unique_ptr<ExprToken>>;

class Expr {
public:

	explicit Expr(const char *str);

	explicit Expr(std::string str);

	double eval() const;

	void print() const;

private:

	std::string _s;

  
	std::vector<std::string> split(const std::string &s) const;

	bool isOp(const std::string &s) const;

	bool isNumber(const std::string &s) const;

	bool isLeftParenthesis(const std::string &s) const;

	bool isLeftParenthesis(char c) const;
	
	bool isRightParenthesis(const std::string &s) const;
  
	vecToken toRPN(const std::vector<std::string> &vec) const;
};


#endif //TPCPPM1S1_EXPR_H
