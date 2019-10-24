#include <string>
#include <iostream>
#include <stack>

#include "Expr.hpp"


using vecToken = std::vector<std::unique_ptr<ExprToken>>;


Expr::Expr(const char *str) : s{str} {};

Expr::Expr(const std::string &str) : s{str} {};


//~~~~~~~~~~~~~~~~Public~Methods~~~~~~~~~~~~~~~~~~~~

double Expr::eval() const {
	vecToken tokens = toRPN(split(s));
	if (tokens.empty()) {
		std::cerr << "not a valid expression" << std::endl;
		return 0;
	}

	std::stack<std::unique_ptr<ExprToken>> stack;

	for (auto &t : tokens) {
		if (t->type() == NUMBER) {
			stack.push(std::move(t));
		} else if (t->type() == OP) {
			if (stack.empty()) {
				std::cerr << "not a valid expression" << std::endl;
				return 0;
			}
			std::unique_ptr<ExprToken> b = std::move(stack.top());
			stack.pop();

			if (stack.empty()) {
				std::cerr << "not a valid expression" << std::endl;
				return 0;
			}
			std::unique_ptr<ExprToken> a = std::move(stack.top());
			stack.pop();

			switch (t->op()) {
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
					std::cerr << "??? : " << t->op() << std::endl;
					exit(255);
			}
		}
	}
	return stack.top()->number();
}

void Expr::print() const {
	for (auto &t : toRPN(split(s))) {
		if (t->type() == OP) {
			std::cout << t->op();
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

	while (it != s.end()) {
		//bypassing spaces
		for (; it != s.end() && std::isspace(*it); ++it);

		//reading a number
		bool pointRead{false};
		while (it != s.end() && (std::isdigit(*it) || (*it == '.' && !pointRead))) {
			if (*it == '.') pointRead = true;
			token += *it;
			++it;
		}
		vector.push_back(token);
		token = "";

		//bypassing spaces
		for (; it != s.end() && std::isspace(*it); ++it);

		//reading an op
		if (it != s.end()) {
			token += *it;
			vector.push_back(token);
			token = "";
			++it;
		}
	}


	return vector;
}

bool Expr::isOp(const std::string &s) const {
	return s.length() == 1 && (s == "+" ||
							   s == "-" ||
							   s == "*" ||
							   s == "/");
}

bool Expr::isNumber(const std::string &s) const {
	std::string::const_iterator it = s.begin();
	bool pointRead{false};
	while (it != s.end() && (std::isdigit(*it) || (*it == '.' && !pointRead))) {
		if (*it++ == '.') {
			pointRead = true;
		}
	}
	return !s.empty() && it == s.end() && (s.length() > 1 || !pointRead);
}

vecToken Expr::toRPN(const std::vector<std::string> &vec) const {
	vecToken res;
	std::stack<std::unique_ptr<ExprToken>> stack;

	for (const auto &t : vec) {
		if (isNumber(t)) {
			res.push_back(std::make_unique<ExprTokenNumber>(stod(t)));
		} else if (isOp(t)) {
			std::unique_ptr<ExprTokenOp> token = std::make_unique<ExprTokenOp>(t[0]);
			while (!stack.empty() && *token < *stack.top()) {
				res.push_back(std::move(stack.top()));
				stack.pop();
			}
			stack.push(std::move(token));

		} else {
			vecToken v;
			return v;
		}
	}

	while (!stack.empty()) {
		res.push_back(std::move(stack.top()));
		stack.pop();
	}

	return res;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~