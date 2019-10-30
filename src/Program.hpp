#ifndef TPCPPM1S1_PROGRAM_H
#define TPCPPM1S1_PROGRAM_H

#include <iostream>
#include <unordered_map>

#include "Expr.hpp"

class Program {
private:
	std::istream &_in;
	std::unordered_map<std::string,double> variableMap;

	bool isPartVarName(char c) const;

	bool handleAssignation(std::string &s, int splitInd);

	double evaluateExpression(std::string &s) const;

	std::string extractVariableName(std::string &s) const;
	
public:
	explicit Program(std::istream &in);

	void exec();
	
};

#endif //TPCPPM1S1_PROGRAM_H
