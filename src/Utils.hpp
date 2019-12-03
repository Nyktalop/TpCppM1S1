#ifndef TPCPPM1S1_UTILS_HPP
#define TPCPPM1S1_UTILS_HPP

#include <string>

enum Function{
	SIN,
	COS,
	TAN,
	SQRT,
	LOG,
	EXP,
	POW,
	HYP,
	LERP,
	POLY,
	UNDEFINED
};


namespace Utils {
	static inline bool isOp(const std::string &s) {

		return s.length() == 1 && (s == "+" ||
								   s == "-" ||
								   s == "*" ||
								   s == "/");
	}

	static bool isNumber(const std::string &s) {
		std::string::const_iterator it = s.begin();
		bool pointRead{false};

		if (*it == '-') {
			return isNumber(s.substr(1));
		}
		while (it != s.end() && (std::isdigit(*it) || (*it == '.' && !pointRead))) {
			if (*it++ == '.') {
				pointRead = true;
			}
		}

		return !s.empty() && it == s.end() && (s.length() > 1 || !pointRead);
	}

	static inline bool isLeftParenthesis(const std::string &s) {
		return s == "(";
	}

	static inline bool isLeftParenthesis(const char c) {
		return c == '(';
	}

	static inline bool isRightParenthesis(const std::string &s) {
		return s == ")";
	}

	static inline bool isRightParenthesis(const char c) {
		return c == ')';
	}

	static inline bool isPartIdName(char c) {
		return !std::isdigit(c) && !std::isspace(c) && c != ';'
			   && c != '+' && c != '-' && c != '*' && c != '/'
			   && c != '(' && c != ')' && c != '.' && c != '=';
	}

	static Function getFunc(std::string &s) {
		if (s == "sin") {
			return SIN;
		} else if (s == "cos") {
			return COS;
		} else if (s == "tan") {
			return TAN;
		} else if (s == "sqrt") {
			return SQRT;
		} else if (s == "log") {
			return LOG;
		} else if (s == "exp") {
			return EXP;
		} else if (s == "pow") {
			return POW;
		} else if (s == "hypot") {
			return HYP;
		} else if (s == "lerp") {
			return LERP;
		} else if (s == "polynome") {
			return POLY;
		}

		return UNDEFINED;
	}
};


#endif //TPCPPM1S1_UTILS_HPP
