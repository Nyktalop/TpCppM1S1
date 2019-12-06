#ifndef TPCPPM1S1_FUNCTION_HPP
#define TPCPPM1S1_FUNCTION_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

class Function {
protected :
	std::vector<double> _args;

	unsigned fullArgsNumber;

	unsigned nbArgs = 0;

public :
	bool isComplete() const;

	virtual double eval() const = 0;

	virtual std::unique_ptr<Function> addArgs(std::vector<double> newArgs) = 0;

	explicit Function(std::vector<double> args);


};


class Log : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Log(std::vector<double> args);
};

class Sin : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Sin(std::vector<double> args);
};

class Cos : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Cos(std::vector<double> args);
};

class Tan : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Tan(std::vector<double> args);
};

class Sqrt : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Sqrt(std::vector<double> args);
};

class Exp : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Exp(std::vector<double> args);
};

class Pow : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Pow(std::vector<double> args);
};

class Hypot : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Hypot(std::vector<double> args);
};

class Lerp : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Lerp(std::vector<double> args);
};
#endif //TPCPPM1S1_FUNCTION_HPP
