#include "Expr.hpp"

using vecToken = std::vector<std::unique_ptr<ExprToken>>;


Expr::Expr(const char *str) : _s{str} {};

Expr::Expr(std::string str) : _s{std::move(str)} {};


//~~~~~~~~~~~~~~~~Public~Methods~~~~~~~~~~~~~~~~~~~~

double Expr::eval() const {
	vecToken tokens = toRPN(split(_s));
	if (tokens.empty()) {
		std::cerr << "Not a valid expression" << std::endl;
		return std::nan("");
	}

	std::stack<std::unique_ptr<ExprToken>> stack;
	for (auto &t : tokens) {
		if (t->type() == NUMBER) {
			stack.push(std::move(t));
		} else if (t->type() == CHAR) {
			if (stack.empty()) {
				std::cerr << "Not a valid expression" << std::endl;
				return std::nan("");
			}
			std::unique_ptr<ExprToken> b = std::move(stack.top());
			stack.pop();

			if (stack.empty()) {
				std::cerr << "Not a valid expression" << std::endl;
				return std::nan("");
			}
			std::unique_ptr<ExprToken> a = std::move(stack.top());
			stack.pop();

			switch (t->character()) {
				case '+' :
					stack.push(std::make_unique<ExprTokenNumber>(a->number() + b->number()));
					break;

				case '-' :
					stack.push(std::make_unique<ExprTokenNumber>(a->number() - b->number()));
					break;

				case '*' :
					stack.push(std::make_unique<ExprTokenNumber>(a->number() * b->number()));
					break;

				case '/' :
					stack.push(std::make_unique<ExprTokenNumber>(a->number() / b->number()));
					break;

				default :
					std::cerr << "Invalid expression (unknown token) : '" << t->character() << "'" << std::endl;
					return std::nan("");
			}
		}
	}

	//missing operators, assumed to be '*' ( 'x(y+z)' case )
	while (stack.size() > 1) {
		std::unique_ptr<ExprToken> b = std::move(stack.top());
		stack.pop();
		std::unique_ptr<ExprToken> a = std::move(stack.top());
		stack.pop();
		stack.push(std::make_unique<ExprTokenNumber>(a->number() * b->number()));
	}
	return stack.top()->number();
}

void Expr::print() const {
	for (auto &t : toRPN(split(_s))) {
		if (t->type() == CHAR) {
			std::cout << t->character();
		} else if (t->type() == NUMBER) {
			std::cout << t->number();
		} else if (t->type() == NONE) {
			std::cout << "NONE";
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~Private~Methods~~~~~~~~~~~~~~~~~~~~

std::vector<std::string> Expr::split(const std::string &s) const {
	std::string token;
	std::vector<std::string> vector;

	std::string::const_iterator it = s.begin();

	bool hasAdvanced = true;
	while (it != s.end() && hasAdvanced) {
		hasAdvanced = false;
		//bypassing spaces
		for (; it != s.end() && std::isspace(*it); ++it);

		//reading an unary '-'
		if (*it == '-') {
			vector.emplace_back("-1");
			vector.emplace_back("*");
			++it;
			hasAdvanced = true;
		}

		//reading a number
		bool pointRead{false};
		while (it != s.end() && (std::isdigit(*it) || (*it == '.' && !pointRead))) {
			if (*it == '.') pointRead = true;
			token += *it;
			++it;
			hasAdvanced = true;
		}

		//if a number is read
		if (!token.empty()) {
			vector.push_back(token);
			token = "";
		}

		//bypassing spaces
		for (; it != s.end() && std::isspace(*it); ++it);

		//reading an character or parenthesis
		if (it != s.end()) {
			token += *it;
			//std::cout << token << std::endl;
			if (Utils::isOp(token) || Utils::isLeftParenthesis(token) || Utils::isRightParenthesis(token)) {
				vector.push_back(token);
				++it;
				hasAdvanced = true;
			}
			token = "";
		}
	}

	return vector;
}

vecToken Expr::toRPN(const std::vector<std::string> &vec) const {
	vecToken res;
	std::stack<std::unique_ptr<ExprToken>> stack;

	for (const auto &t : vec) {
		if (Utils::isNumber(t)) {
			res.push_back(std::make_unique<ExprTokenNumber>(stod(t)));


		} else if (Utils::isOp(t)) {
			std::unique_ptr<ExprTokenChar> token = std::make_unique<ExprTokenChar>(t[0]);
			while (!stack.empty() && *token < *stack.top()) {
				res.push_back(std::move(stack.top()));
				stack.pop();
			}
			stack.push(std::move(token));


		} else if (Utils::isLeftParenthesis(t)) {
			std::unique_ptr<ExprTokenChar> token = std::make_unique<ExprTokenChar>(t[0]);
			stack.push(std::move(token));

		} else if (Utils::isRightParenthesis(t)) {
			while (!stack.empty() && !Utils::isLeftParenthesis(stack.top()->character())) {
				res.push_back(std::move(stack.top()));
				stack.pop();
			}
			if (!stack.empty()) {
				stack.pop();
			} else {
				return {};
			}
		} else {
			return {};
		}
	}

	while (!stack.empty()) {
		res.push_back(std::move(stack.top()));
		stack.pop();
	}

	return res;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
