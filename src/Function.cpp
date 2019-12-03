#include "Function.hpp"

/*--------------------------------FUNCTION--------------------------------*/
Function::Function(std::vector<double> args): _args{args}, nbArgs{0} {

}
/*------------------------------------------------------------------------*/


/*-----------------------------------LOG----------------------------------*/
bool Log::isComplete () const{
	return _args.size() == fullArgsNumber;
}

double Log::eval() const{
	if(isComplete()){
		return log(_args[0]);
	}
	std::cerr << "The function 'log' is evaluable : not complete" << std::endl;
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
	for(const auto &d : _args){
		if(!std::isnan(d)) {
			nbArgs++;
		}
	}
}
/*-------------------------------------------------------------------------*/