#include "Program.hpp"


Program::Program(std::istream &in) : _in{in} {
	//generating base functions
	functionMap["log"] = std::make_unique<Log>();
	functionMap["cos"] = std::make_unique<Cos>();
	functionMap["sin"] = std::make_unique<Sin>();
	functionMap["tan"] = std::make_unique<Tan>();
	functionMap["sqrt"] = std::make_unique<Sqrt>();
	functionMap["exp"] = std::make_unique<Exp>();
	functionMap["pow"] = std::make_unique<Pow>();
	functionMap["hypot"] = std::make_unique<Hypot>();
	functionMap["lerp"] = std::make_unique<Lerp>();
	functionMap["ident"] = std::make_unique<Id>();

};

bool Program::isFunc(std::string &s) const {
	return functionMap.find(s) != functionMap.end();
}


bool Program::handleAssignation(std::string &s, unsigned splitInd) {

	std::string var = s.substr(0, splitInd);
	std::string expr = s.substr(splitInd + 1, -1);

	Func result = evaluateExpression(expr);
	std::string name = extractVariableName(var);

	if (Utils::isBaseFunc(name)) {
		std::cerr << "Unable to use '" << name << "' as variable name : is a basic function" << std::endl;
		return false;
	}

	if (result != nullptr && !name.empty()) {
		if(result->isComplete()) {
			functionMap[name] = std::make_unique<Id>(std::vector{result->eval()});
			std::cout << "result : " << result->eval() << " saved under the name '" << name << "'" << std::endl;
		}
		else {
			functionMap[name] = std::move(result);
			std::cout << "partial function : " << functionMap[name]->repr() << " saved under the name '" << name << "'" << std::endl;
		}
	} else {
		return false;
	}

	return true;
}


Func Program::evaluateExpression(std::string &s) const {
	std::string::const_iterator it = s.begin();
	std::string var;
	std::string buf;
	while (it != s.end()) {
		while (it != s.end() && Utils::isPartIdName(*it)) {
			var += *it;
			++it;
		}
		if (!var.empty()) {
			if (isFunc(var)) {
				//reading the function args
				if (it != s.end() && Utils::isLeftParenthesis(*it)) {
					//omitting the first '('
					++it;
					std::vector<double> args;
					std::string argbuf;
					unsigned parenthesisCount = 1;
					unsigned partialCount = 1;

					//until the end of the args
					while (it != s.end() && parenthesisCount != 0) {
						if (Utils::isRightParenthesis(*it)) {
							//omitting the last ')'
							if (--parenthesisCount != 0) {
								argbuf += *it;
							}
						} else if (Utils::isLeftParenthesis(*it)) {
							++parenthesisCount;
							argbuf += *it;
						} else if (*it != ',') {
							argbuf += *it;
						} else if (!argbuf.empty()) {
							//if not in a nested func usage ( pow(1,pow(2,3)) )
							if (parenthesisCount <= 1) {
								//placeholder or expression ?
								bool isPlaceholder = false;
								auto it_argbuf = argbuf.begin();
								while(it_argbuf != argbuf.end() && std::isspace(*it_argbuf)) {it_argbuf++;}
								if(it_argbuf != argbuf.end()) {
									if (*it_argbuf == '_') {
										if(it_argbuf+1 != argbuf.end() && *(it_argbuf+1) != ' ') {
											std::string number;
											++it_argbuf;
											while(it_argbuf != argbuf.end()) {
												if(!std::isspace(*it_argbuf))
													number += *it_argbuf;
												it_argbuf++;
											}
											if(number == std::to_string(partialCount)) {
													isPlaceholder = true;
													partialCount++;
											} else {
													std::cerr << "Wrong number in placeholder, should be " << partialCount << std::endl;
													return nullptr;
											}
										} else {
											std::cerr << "Invalid expression '_', this needs a number [0-9] to be a placeholder" << std::endl;
											return nullptr;
										}

									}
								}
								if(isPlaceholder) {
									args.push_back(std::nan(""));
								} else {
									Func resFunc = evaluateExpression(argbuf);
									if (resFunc == nullptr || !resFunc->isComplete()) {
										std::cerr << "Expression : '" << argbuf << "' is invalid (used in '" << var
												  << "')" << std::endl;
										return nullptr;
									}
									args.push_back(resFunc->eval());
								}
								argbuf = "";
							} else {
								argbuf += *it;
							}
						}
						++it;
					}

					if (!argbuf.empty()) {
						//placeholder or expression ?
						bool isPlaceholder = false;
						auto it_argbuf = argbuf.begin();
						while(it_argbuf != argbuf.end() && std::isspace(*it_argbuf)) {it_argbuf++;}
						if(it_argbuf != argbuf.end()) {
							if (*it_argbuf == '_') {
								if(it_argbuf+1 != argbuf.end() && *(it_argbuf+1) != ' ') {
									std::string number;
									++it_argbuf;
									while(it_argbuf != argbuf.end()) {
										if(!std::isspace(*it_argbuf))
											number += *it_argbuf;
										it_argbuf++;
									}
									if(number == std::to_string(partialCount)) {
										isPlaceholder = true;
									} else {
										std::cerr << "Wrong number in placeholder, should be " << partialCount << std::endl;
										return nullptr;
									}
								} else {
									std::cerr << "Invalid expression '_', this needs a number [0-9] to be a placeholder" << std::endl;
									return nullptr;
								}

							}
						}
						if(isPlaceholder) {
							args.push_back(std::nan(""));
						} else {
							Func resFunc = evaluateExpression(argbuf);
							if (resFunc == nullptr || !resFunc->isComplete()) {
								std::cerr << "Expression : '" << argbuf << "' is invalid (used in '" << var
										  << "')" << std::endl;
								return nullptr;
							}
							args.push_back(resFunc->eval());
						}
					}

					if (parenthesisCount != 0) {
						std::cerr << "Misuse (parenthesis missing) of function identifier : '" << var << "'"
								  << std::endl;
						return nullptr;
					}

					Func resFunc = functionMap.at(var)->addArgs(args);

					if (resFunc != nullptr) {
						if(resFunc->isComplete()) {
							buf += std::to_string(resFunc->eval());

						//if the function is partial, return the new func
						} else {
							//checking if the partial function is the only thing in the expression
							bool simpleUse = true;
							//nothing but spaces before
							for(char c : buf) {
								if(!std::isspace(c)) {
									simpleUse = false;
								}
							}
							//nothing but spaces and ';' after
							while (it != s.end()) {
								if(!std::isspace(*it) && *it != ';') {
									simpleUse = false;
								}
								it++;
							}
							if (simpleUse) {
								return resFunc;
							} else {
								std::cerr << "Invalid use of partial definition in complex expression '" << var << "'"
										  << std::endl;
								return nullptr;
							}
						}
					} else {
						return nullptr;
					}
				} else if (functionMap.find(var) != functionMap.end()) {
					if(functionMap.at(var)->isComplete()) {
						buf += std::to_string(functionMap.at(var)->eval());
					} else {
						//checking if the partial function is the only thing in the expression
						bool simpleUse = true;
						//nothing but spaces before
						for(char c : buf) {
							if(!std::isspace(c)) {
								simpleUse = false;
							}
						}
						//nothing but spaces and ';' after
						while (it != s.end()) {
							if(!std::isspace(*it) && *it != ';') {
								simpleUse = false;
							}
							it++;
						}
						if (simpleUse) {
							return functionMap.at(var)->addArgs({});
						} else {
							std::cerr << "Invalid use of partial definition in complex expression '" << var << "'"
									  << std::endl;
							return nullptr;
						}
					}
				}
			} else {
				std::cerr << "Unknown identifier in expression : '" << var << "'" << std::endl;
				return nullptr;
			}
		}
		var = "";
		if (it != s.end()) {
			buf += *it;
			++it;
		}

	}

	Expr e{buf};
	return std::make_unique<Id>(std::vector {e.eval()});
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
		s  = s.substr(0,s.find('#')); //handling python-style comments
		if (!s.empty()) {
			if (s[s.find_last_not_of(" \t\r")] == ';') {
				unsigned splitInd = s.find('=');
				if (splitInd != -1) {
					handleAssignation(s, splitInd);
				}

			} else {
				if (s.find('=') != -1) {
					std::cerr << "Invalid assignation instruction, maybe you forgot ';'" << std::endl;
				} else {
					Func resFunc = evaluateExpression(s);
					if (resFunc != nullptr) {
						if(resFunc->isComplete()) {
							std::cout << resFunc->eval() << std::endl;
						} else {
							std::cout << "partial function : " << resFunc->repr() << std::endl;
						}
					}
				}
			}
		}
	}
}

