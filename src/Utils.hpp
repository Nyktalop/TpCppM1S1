#ifndef TPCPPM1S1_UTILS_HPP
#define TPCPPM1S1_UTILS_HPP

#include <string>

namespace Utils {
	static inline bool isBaseFunc(const std::string& s) {
		return s == "sin" || s == "cos" || s == "tan" || s == "log"
			|| s == "exp" || s == "sqrt"|| s == "pow" || s == "hyp"
			|| s == "lerp"|| s == "ident" ||s == "polynome";
	}

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
};


#endif //TPCPPM1S1_UTILS_HPP
