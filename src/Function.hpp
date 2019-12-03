#ifndef TPCPPM1S1_FUNCTION_HPP
#define TPCPPM1S1_FUNCTION_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

class Function {
protected :
	std::vector<double> _args;

	unsigned nbArgs = 0;

public :
	virtual bool isComplete() const = 0;

	virtual double eval() const = 0;

	virtual std::unique_ptr<Function> addArgs(std::vector<double> newArgs) = 0;

	explicit Function(std::vector<double> args);


};


class Log : public Function {
private:
	const unsigned fullArgsNumber = 1;

public:
	bool isComplete () const override;

	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Log(std::vector<double> args);
};

#endif //TPCPPM1S1_FUNCTION_HPP
