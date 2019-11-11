#ifndef TPCPPM1S1_PROGRAM_H
#define TPCPPM1S1_PROGRAM_H

#include <iostream>
#include <unordered_map>

#include "Expr.hpp"
#include "Utils.hpp"


class Program {
private:
	std::istream &_in;
	std::unordered_map<std::string, double> variableMap;

	bool handleAssignation(std::string &s, unsigned splitInd);

	double evaluateExpression(std::string &s) const;

	std::string extractVariableName(std::string &s) const;

	double execFunction(Function func, const std::vector<double> &args) const;

public:
	explicit Program(std::istream &in);

	void exec();

};

#endif //TPCPPM1S1_PROGRAM_H
