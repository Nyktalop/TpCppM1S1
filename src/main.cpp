#include <iostream>
#include "Program.hpp"

int main() {

	Program prog{std::cin};

	prog.exec();

	return 0;
}

/*
double Program::execFunction(const Function func, const std::vector<double> &args) const {
	switch (func) {
		case SIN :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'sin', should be 1" << std::endl;
				return std::nan("");
			}
			return sin(args[0]);

		case COS :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'cos', should be 1" << std::endl;
				return std::nan("");
			}
			return cos(args[0]);

		case TAN :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'tan', should be 1" << std::endl;
				return std::nan("");
			}
			return tan(args[0]);

		case SQRT :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'sqrt', should be 1" << std::endl;
				return std::nan("");
			} else if (args[0] < 0) {
				std::cerr << "Negative argument for function 'sqrt' : " << args[0] << std::endl;
				return std::nan("");
			}
			return sqrt(args[0]);

		case LOG :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'log', should be 1" << std::endl;
				return std::nan("");
			} else if (args[0] <= 0) {
				std::cerr << "Negative or zero argument for function 'log' : " << args[0] << std::endl;
				return std::nan("");
			}
			return log(args[0]);

		case EXP :
			if (args.size() != 1) {
				std::cerr << "Invalid number of arguments for function 'exp', should be 1" << std::endl;
				return std::nan("");
			}
			return exp(args[0]);

		case POW :
			if (args.size() != 2) {
				std::cerr << "Invalid number of arguments for function 'pow', should be 2" << std::endl;
				return std::nan("");
			}
			return pow(args[0], args[1]);

		case HYP :
			if (args.size() != 2) {
				std::cerr << "Invalid number of arguments for function 'hypot', should be 2" << std::endl;
				return std::nan("");
			} else if (args[0] < 0 || args[1] < 0) {
				std::cerr << "Arguments of 'hypot' should not be negative" << std::endl;
				return std::nan("");
			}
			return sqrt(pow(args[0], 2) + pow(args[1], 2));

		case LERP :
			if (args.size() != 3) {
				std::cerr << "Invalid number of arguments for function 'lerp', should be 3" << std::endl;
				return std::nan("");
			} else if (args[2] < 0) {
				std::cerr << "Argument 3 of 'lerp' should be >= 0" << std::endl;
				return std::nan("");
			} else if (args[2] > 1) {
				std::cerr << "Argument 3 of 'lerp' should be <= 1" << std::endl;
				return std::nan("");
			}
			return args[0] + args[2] * (args[1] - args[0]);

		case POLY : {
			if (args.size() <= 1 || args.size() != args[0] + 3) {
				std::cerr
						<< "Invalid number of arguments for function 'polynome', should be polynome(degree, [list of coeff (degree+1)], variable)"
						<< std::endl;
				return std::nan("");
			} else if (args.back() == 0) {
				std::cerr << "Variable should not be 0 in 'polynome'" << std::endl;
			}
			double res = 0;
			for (int i = 0; i <= args[0]; ++i) {
				res += args[i + 1] * pow(args.back(), i);
			}
			return res;
		}

		default :
			return std::nan("");
	}

} */