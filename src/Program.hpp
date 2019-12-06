#ifndef TPCPPM1S1_PROGRAM_H
#define TPCPPM1S1_PROGRAM_H

#include <iostream>
#include <unordered_map>
#include <memory>

#include "Expr.hpp"
#include "Utils.hpp"
#include "Function.hpp"

using Func = std::unique_ptr<Function>;

class Program {
private:
	std::istream &_in;
	std::unordered_map<std::string, std::unique_ptr<Function>> functionMap;

	bool handleAssignation(std::string &s, unsigned splitInd);

	Func evaluateExpression(std::string &s) const;

	std::string extractVariableName(std::string &s) const;

	bool isFunc(std::string& s) const;

public:
	explicit Program(std::istream &in);

	void exec();

};

#endif //TPCPPM1S1_PROGRAM_H
