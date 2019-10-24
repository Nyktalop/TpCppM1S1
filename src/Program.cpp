#include <iostream>

#include "Program.hpp"
#include "Expr.hpp"


Program::Program(std::istream &in) : _in{in} {};

void Program::exec() const {
	std::string s;
	while (std::getline(_in, s) && s != "q" && s != "quit") {
		if (!s.empty()) {
			if (s[s.find_last_not_of(" \t\r")] == ';') {
			} else {
				Expr e{s};
				std::cout << e.eval() << std::endl;
			}
		}
	}
}

