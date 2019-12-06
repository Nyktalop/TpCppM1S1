#include "Function.hpp"

/*--------------------------------FUNCTION--------------------------------*/
Function::Function(std::vector<double> args, unsigned fullA, std::string name): _args{args}, _fullArgsNumber{fullA}, _baseFuncName{name} {
	for(const auto &d : _args){
		if(!std::isnan(d)) {
			_nbArgs++;
		}
	}
}

Function::Function(unsigned fullA, std::string name) : _fullArgsNumber{fullA}, _baseFuncName{name} {}

std::string Function::repr() const {
	unsigned nbPlace = 1;
	std::string argsRepr;
	for(int i = 0;i<_fullArgsNumber;++i) {
		if(i < _args.size()) {
			if (std::isnan(_args[i])) {
				argsRepr.append("_" + std::to_string(nbPlace++));
			} else {
				argsRepr.append(std::to_string(_args[i]));
			}
		} else {
			argsRepr.append("_" + std::to_string(nbPlace++));
		}

		if(i != _fullArgsNumber-1) {
			argsRepr.append(", ");
		}
	}

	return _baseFuncName + "(" + argsRepr + ")";
}

bool Function::isComplete () const{
	return _nbArgs == _fullArgsNumber;
}

/*------------------------------------------------------------------------*/


/*-----------------------------------LOG----------------------------------*/
double Log::eval() const{
	if(isComplete()){
		return log(_args[0]);
	}
	std::cerr << "The function 'log' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Log::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Log>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'log'" << std::endl;
	return nullptr;
}

Log::Log(std::vector<double> args): Function(args, 1, "log") {}

Log::Log(): Function(1, "log") {}

/*-------------------------------------------------------------------------*/

/*-----------------------------------SIN-----------------------------------*/
double Sin::eval() const{
	if(isComplete()){
		return sin(_args[0]);
	}
	std::cerr << "The function 'sin' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Sin::addArgs(std::vector<double> newArgs){

	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Sin>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'sin'" << std::endl;
	return nullptr;
}

Sin::Sin(std::vector<double> args): Function(args, 1, "sin") {}

Sin::Sin(): Function(1, "sin") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------COS-----------------------------------*/
double Cos::eval() const{
	if(isComplete()){
		return cos(_args[0]);
	}
	std::cerr << "The function 'cos' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Cos::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Cos>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'cos'" << std::endl;
	return nullptr;
}

Cos::Cos(std::vector<double> args): Function(args, 1, "cos") {}

Cos::Cos(): Function(1, "cos") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------TAN-----------------------------------*/
double Tan::eval() const{
	if(isComplete()){
		return tan(_args[0]);
	}
	std::cerr << "The function 'tan' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Tan::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Tan>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'tan'" << std::endl;
	return nullptr;
}

Tan::Tan(std::vector<double> args): Function(args, 1, "tan") {}

Tan::Tan(): Function(1, "tan") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------SQRT-----------------------------------*/
double Sqrt::eval() const{
	if(isComplete()){
		return sqrt(_args[0]);
	}
	std::cerr << "The function 'sqrt' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Sqrt::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Sqrt>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'sqrt'" << std::endl;
	return nullptr;
}

Sqrt::Sqrt(std::vector<double> args): Function(args, 1, "sqrt") {}

Sqrt::Sqrt(): Function(1, "sqrt") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------EXP-----------------------------------*/
double Exp::eval() const{
	if(isComplete()){
		return exp(_args[0]);
	}
	std::cerr << "The function 'exp' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Exp::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Exp>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'exp'" << std::endl;
	return nullptr;
}

Exp::Exp(std::vector<double> args): Function(args, 1, "exp") {}

Exp::Exp(): Function(1, "exp") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------POW-----------------------------------*/
double Pow::eval() const{
	if(isComplete()){
		return pow(_args[0],_args[1]);
	}
	std::cerr << "The function 'pow' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Pow::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Pow>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'pow'" << std::endl;
	return nullptr;
}

Pow::Pow(std::vector<double> args): Function(args, 2, "pow") {}

Pow::Pow(): Function(2, "pow") {}
/*-------------------------------------------------------------------------*/

/*----------------------------------HYPOT----------------------------------*/
double Hypot::eval() const{
	if(isComplete()){
		return sqrt(pow(_args[0], 2) + pow(_args[1], 2));
	}
	std::cerr << "The function 'hypot' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Hypot::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Hypot>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'hypot'" << std::endl;
	return nullptr;
}

Hypot::Hypot(std::vector<double> args): Function(args, 2, "hypot") {}

Hypot::Hypot(): Function(2, "hypot") {}
/*-------------------------------------------------------------------------*/

/*----------------------------------LERP-----------------------------------*/
double Lerp::eval() const{
	if(isComplete()){
		return _args[0] + _args[2] * (_args[1] - _args[0]);
	}
	std::cerr << "The function 'lerp' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Lerp::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Lerp>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'lerp'" << std::endl;
	return nullptr;
}

Lerp::Lerp(std::vector<double> args): Function(args, 3, "lerp") {}

Lerp::Lerp(): Function(3, "lerp") {}
/*-------------------------------------------------------------------------*/

/*-----------------------------------ID------------------------------------*/
double Id::eval() const{
	if(isComplete()){
		return _args[0];
	}
	std::cerr << "The function 'id' is not evaluable : not complete" << std::endl;
	return std::nan("");
}

std::unique_ptr<Function> Id::addArgs(std::vector<double> newArgs){
	if (_nbArgs + newArgs.size() <= _fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != vec.end() && it_new != newArgs.end()) {
			if(std::isnan(*it_args)) {
				*it_args = *it_new;
				it_new++;
			}
			it_args++;
		}
		while(it_new != newArgs.end()) {
			vec.push_back(*it_new);
			it_new++;
		}

		return std::make_unique<Id>(vec);
	}

	std::cerr << "Wrong number of arguments for function type 'id'" << std::endl;
	return nullptr;
}

Id::Id(std::vector<double> args): Function(args, 1, "ident") {}

Id::Id(): Function(1, "ident") {}
/*-------------------------------------------------------------------------*/