#include "Function.hpp"

/*--------------------------------FUNCTION--------------------------------*/
Function::Function(std::vector<double> args): _args{args} {
	for(const auto &d : _args){
		if(!std::isnan(d)) {
			nbArgs++;
		}
	}
}

bool Function::isComplete () const{
	return nbArgs == fullArgsNumber;
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Log::Log(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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

	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Sin::Sin(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Cos::Cos(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Tan::Tan(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Sqrt::Sqrt(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Exp::Exp(std::vector<double> args): Function(args) {
	fullArgsNumber = 1;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Pow::Pow(std::vector<double> args): Function(args) {
	fullArgsNumber = 2;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Hypot::Hypot(std::vector<double> args): Function(args) {
	fullArgsNumber = 2;
}
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
	if (nbArgs + newArgs.size() <= fullArgsNumber) {
		auto vec = _args;
		auto it_args = vec.begin();
		auto it_new = newArgs.begin();
		while(it_args != _args.end() && it_new != newArgs.end()) {
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

Lerp::Lerp(std::vector<double> args): Function(args) {
	fullArgsNumber = 2;
}
/*-------------------------------------------------------------------------*/