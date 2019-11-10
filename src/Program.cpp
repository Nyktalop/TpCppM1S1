#include "Program.hpp"


Program::Program(std::istream &in) : _in{in} {};

bool Program::handleAssignation(std::string &s, unsigned splitInd) {

    std::string var = s.substr(0, splitInd);
    std::string expr = s.substr(splitInd + 1, -1);

    double result = evaluateExpression(expr);
    std::string name = extractVariableName(var);

    if(Utils::getFunc(name) != UNDEFINED) {
        std::cerr << "Unable to use '" << name << "' as variable name : is a function" << std::endl;
        return false;
    }

    if (!std::isnan(result) && !name.empty()) {
        variableMap[name] = result;
        std::cout << "result (" << result << ") saved under the name '" << name << "'" << std::endl;
    } else {
        return false;
    }

    return true;
}

double Program::execFunction(const Function func, const std::vector<double> &args) const {
    switch(func) {
        case SIN :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'sin', should be 1" << std::endl;
                return std::nan("");
            }
            return sin(args[0]);

        case COS :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'cos', should be 1" << std::endl;
                return std::nan("");
            }
            return cos(args[0]);

        case TAN :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'tan', should be 1" << std::endl;
                return std::nan("");
            }
            return tan(args[0]);

        case SQRT :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'sqrt', should be 1" << std::endl;
                return std::nan("");
            } else if (args[0] < 0) {
                std::cerr << "Negative argument for function 'sqrt' : " << args[0] << std::endl;
                return std::nan("");
            }
            return sqrt(args[0]);

        case LOG :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'log', should be 1" << std::endl;
                return std::nan("");
            } else if (args[0] <= 0) {
                std::cerr << "Negative or zero argument for function 'log' : " << args[0] << std::endl;
                return std::nan("");
            }
            return log(args[0]);

        case EXP :
            if(args.size() != 1) {
                std::cerr << "Invalid number of arguments for function 'exp', should be 1" << std::endl;
                return std::nan("");
            }
            return exp(args[0]);

        case POW :
            if(args.size() != 2) {
                std::cerr << "Invalid number of arguments for function 'pow', should be 2" << std::endl;
                return std::nan("");
            } else if (args[0] == 0) {
                std::cerr << "Argument 1 of 'pow' should not be zero" << std::endl;
                return std::nan("");
            }
            return pow(args[0],args[1]);

        case HYP :
            if(args.size() != 2) {
                std::cerr << "Invalid number of arguments for function 'hypot', should be 2" << std::endl;
                return std::nan("");
            } else if (args[0] < 0 || args[1] < 0) {
                std::cerr << "Arguments of 'hypot' should not be negative" << std::endl;
                return std::nan("");
            }
            return sqrt(pow(args[0],2) + pow(args[1],2));

        case LERP :
            if(args.size() != 3) {
                std::cerr << "Invalid number of arguments for function 'lerp', should be 3" << std::endl;
                return std::nan("");
            } else if (args[2] < 0) {
                std::cerr << "Argument 3 of 'lerp' should be >= 0" << std::endl;
                return std::nan("");
            } else if (args[2] > 1) {
                std::cerr << "Argument 3 of 'lerp' should be <= 1" << std::endl;
                return std::nan("");
            }
            return args[0]+args[2]*(args[1]-args[0]);

        case POLY : {
            if (args.size() <= 1 || args.size() != args[0] + 3) {
                std::cerr
                        << "Invalid number of arguments for function 'polynome', shoulde be polynome(degree, [list of coeff (degree+1)], variable)"
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

}

double Program::evaluateExpression(std::string &s) const {
    std::string::const_iterator it = s.begin();
    std::string var;
    std::string buf;
    while (it != s.end()) {
        while (it != s.end() && Utils::isPartIdName(*it)) {
            var += *it;
            ++it;
        }
        if (!var.empty()) {
            Function func;
            if( (func = Utils::getFunc(var)) != UNDEFINED) {
                //reading the function args
                if(it != s.end() && Utils::isLeftParenthesis(*it)) {
                    //omitting the first '('
                    ++it;
                    std::vector<double> args;
                    std::string argbuf;
                    unsigned parCount = 1;

                    //until the end of the args
                    while(it != s.end() && parCount != 0) {
                        if(Utils::isRightParenthesis(*it)) {
                            //omitting the last ')'
                            if(--parCount!=0) {
                                argbuf += *it;
                            }
                        } else if (Utils::isLeftParenthesis(*it)) {
                            ++parCount;
                            argbuf += *it;
                        } else if(*it != ',') {
                            argbuf += *it;
                        } else if (!argbuf.empty()){
                            //if not in a nested func usage ( pow(1,pow(2,3)) )
                            if(parCount <= 1) {
                                double res = evaluateExpression(argbuf);
                                if (std::isnan(res)) {
                                    std::cerr << "Expression : '" << argbuf << "' is invalid" << std::endl;
                                    return std::nan("");
                                }
                                args.push_back(res);
                                argbuf = "";
                            } else {
                                argbuf += *it;
                            }
                        }
                        ++it;
                    }

                    if(!argbuf.empty()) {
                        double res = evaluateExpression(argbuf);
                        if(std::isnan(res)) {
                            std::cerr << "Expression : '" << argbuf << "' is invalid" << std::endl;
                            return std::nan("");
                        }
                        args.push_back(res);
                    }

                    if(parCount != 0) {
                        std::cerr << "Misuse (parenthesis missing) of function identifier : '" << var << "'" << std::endl;
                        return std::nan("");
                    }

                    double res = execFunction(func, args);

                    if(!std::isnan(res)) {
                        buf += std::to_string(res);
                    } else {
                        return res;
                    }
                } else {
                    std::cerr << "Misuse (no args) of function identifier : '" << var << "'"  <<std::endl;
                    return std::nan("");
                }
            }
            else if (variableMap.find(var) != variableMap.end()) {
                buf += std::to_string(variableMap.at(var));
            } else {
                std::cerr << "Unknown identifier in expression : '" << var << "'" << std::endl;
                return std::nan("");
            }
        }
        var = "";
        if (it != s.end()) {
            buf += *it;
            ++it;
        }

    }

    Expr e{buf};
    return e.eval();
}

std::string Program::extractVariableName(std::string &s) const {
    std::string var;
    std::string::const_iterator it = s.begin();

    while (it != s.end()) {
        //bypassing spaces
        for (; it != s.end() && std::isspace(*it); ++it);

        while (it != s.end() && !std::isspace(*it)) {
            if (!Utils::isPartIdName(*it)) {
                std::cerr << "Invalid char in identifier : '" << *it << "'";
                if (*it == '=') {
                    std::cerr << " maybe you forgot ';' ?";
                }
                std::cerr << std::endl;
                return "";
            }
            var += *it++;
        }

        //bypassing spaces
        for (; it != s.end() && std::isspace(*it); ++it);
    }

    return var;
}

void Program::exec() {
    std::string s;
    while (std::getline(_in, s) && s != "q" && s != "quit" && s != "exit") {
        if (!s.empty()) {
            if (s[s.find_last_not_of(" \t\r")] == ';') {
                unsigned splitInd = s.find('=');
                if (splitInd != -1) {
                    handleAssignation(s, splitInd);
                }

            } else {
                if(s.find('=') != -1) {
                    std::cerr << "Invalid assignation instruction, maybe you forgot ';'" << std::endl;
                } else {
                    double res = evaluateExpression(s);
                    if (!std::isnan(res)) {
                        std::cout << res << std::endl;
                    }
                }
            }
        }
    }
}

