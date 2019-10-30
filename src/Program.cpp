#include "Program.hpp"


Program::Program(std::istream &in) : _in{in} {};

bool Program::handleAssignation(std::string &s, int splitInd) {

	std::string var = s.substr(0,splitInd);
	std::string expr = s.substr(splitInd+1,-1);

	double result = evaluateExpression(expr);
	std::string name = extractVariableName(var);

	if(!std::isnan(result) && !name.empty()) {
        variableMap[name] = result;
        std::cout << "result (" << result << ") saved under the name '" << name << "'" << std::endl;
	} else {
	    return false;
	}

	return true;
}

bool Program::isPartVarName(char c) const {
    return !std::isdigit(c) && !std::isspace(c) && c != ';'
            && c != '+' && c != '-' && c != '*' && c != '/'
            && c != '(' && c != ')' && c != '.' && c != '=';
}

double Program::evaluateExpression(std::string &s) const {
    std::string::const_iterator it = s.begin();
    std::string var;
    std::string buf;
    while(it != s.end()) {
        while (it != s.end() && isPartVarName(*it)) {
            var += *it;
            ++it;
        }
        if (!var.empty()) {
            if (variableMap.find(var) != variableMap.end()) {
                //std::cout << "variable : " << variableMap[var] << std::endl;
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

	while(it != s.end()) {
		//bypassing spaces
		for (; it != s.end() && std::isspace(*it); ++it);

		while(it != s.end() && !std::isspace(*it)) {
		    if(!isPartVarName(*it)) {
		        std::cerr << "Invalid char in identifier : '" << *it << "'";
		        if(*it == '=') {
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
                int splitInd = s.find('=');
				if(splitInd != -1) {
                    handleAssignation(s,splitInd);
				}
			} else if (!isPartVarName(s.front())){
				double res = evaluateExpression(s);
				if(!std::isnan(res)) {
                    std::cout << res << std::endl;
                }

			} else {
				std::string name = extractVariableName(s);
				if(!name.empty()) {
                    if(variableMap.find(name) != variableMap.end()) {
                        std::cout << variableMap[name] << std::endl;
                    } else {
                        std::cerr << "unknown variable : '" << name << "'" << std::endl;
                    }
                }
			}
		}
	}
}

