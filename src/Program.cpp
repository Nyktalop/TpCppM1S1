#include "Program.hpp"


Program::Program(std::istream &in) : _in{in} {};

bool Program::handleAssignation(std::string &s) {
	int splitInd = s.find('=');

	if(splitInd == -1) {
		std::cerr << "'=' missing" << std::endl;
		return false;
	}
	
	std::string var = s.substr(0,splitInd);
	std::string expr = s.substr(splitInd+1,-1);

	double result = evaluateExpression(expr);
	std::string name = extractVariableName(var); 
	variableMap[name] = result;

	std::cout << "result (" << result << ") saved under the name '" << name << "'" << std::endl;

	
	return true;
}

double Program::evaluateExpression(std::string &s) {
    std::string::const_iterator it = s.begin();
    std::string var;
    std::string buf;
    while(it != s.end()) {
        while (it != s.end() && std::isalpha(*it)) {
            var += *it;
            ++it;
        }
        if (!var.empty()) {
            if (variableMap.find(var) != variableMap.end()) {
                buf += variableMap[var];
            } else {
                std::cerr << "Unknown identifier in expression : '" << var << "'" << std::endl;
                return 0;
            }
        }
        var = "";
        if (it != s.end()) {
            ++it;
            buf += *it;
        }
    }

    std::cout << "buffer :" << buf << std::endl;

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
				if(!handleAssignation(s)) {
					std::cerr << "Not a valid instruction" << std::endl;
				}
			} else if (std::isdigit(s.front())){
				double res = evaluateExpression(s);
				std::cout << res << std::endl;
			} else {
				std::string name = extractVariableName(s);
				std::cout << variableMap[name] << std::endl;
				/*if(variableMap.find(name)) {
					std::cout << variableMap[name] << std::endl;
				} else {
					std::cerr << "Not a valid instruction, maybe you forgot ';', or the variable does not exist" << std::endl;
					}*/
			}
		}
	}
}

