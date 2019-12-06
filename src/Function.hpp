#ifndef TPCPPM1S1_FUNCTION_HPP
#define TPCPPM1S1_FUNCTION_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

class Function {
protected :
	std::vector<double> _args;

	std::string _baseFuncName;

	unsigned _fullArgsNumber;

	unsigned _nbArgs = 0;

public :
	virtual std::string repr()const;

	virtual bool isComplete() const;

	virtual double eval() const = 0;

	virtual std::unique_ptr<Function> addArgs(std::vector<double> newArgs) = 0;

	explicit Function(std::vector<double> args, unsigned fullA, std::string name);

	explicit Function(unsigned fullA, std::string name);


};


class Log : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Log(std::vector<double> args);

	explicit Log();
};

class Sin : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Sin(std::vector<double> args);

	explicit Sin();
};

class Cos : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Cos(std::vector<double> args);

	explicit Cos();
};

class Tan : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Tan(std::vector<double> args);

	explicit Tan();
};

class Sqrt : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Sqrt(std::vector<double> args);

	explicit Sqrt();
};

class Exp : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Exp(std::vector<double> args);

	explicit Exp();
};

class Pow : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Pow(std::vector<double> args);

	explicit Pow();
};

class Hypot : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Hypot(std::vector<double> args);

	explicit Hypot();
};

class Lerp : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Lerp(std::vector<double> args);

	explicit Lerp();
};

class Id : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	explicit Id(std::vector<double> args);

	explicit Id();
};

class Poly : public Function {
public:
	double eval() const override;

	std::unique_ptr<Function> addArgs(std::vector<double> newArgs) override;

	std::string repr()const override;

	bool isComplete() const override;

	explicit Poly(std::vector<double> args);

	explicit Poly();
};

#endif //TPCPPM1S1_FUNCTION_HPP
