#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>

enum Types {
	CHAR = 0,
	INT = 1,
	SHORT = 2,
	MAX = 3,
	PTR = 4
};

bool isNumber(char _c) {
	return _c == '0' || _c == '1' || _c == '2' || _c == '3' || _c == '4' || _c == '5' || _c == '6' || _c == '7' || _c == '8' || _c == '9' || _c == '-';
}
bool isNumber(const std::string& _s) {
	return isNumber(_s[0]);
}

struct Variable {
	void* value;
	Types type;
	bool isUnsigned;
	bool isPointer;
};

#define checkType(name, type) \
	if(keys[2] == #name) {\
		void* var;\
		if(isUnsigned) {\
			var = new unsigned type;\
		} else {\
			var = new signed type;\
		}\
		variables_new[keys[1]] = Variable{var, Types::name, isUnsigned, isPointer};\
		created = true;\
	}

#define mathAutomator_varCheck(iterator, dest, keynum, operation, count, ...) \
	if(iterator != variables.end()) { \
		Variable s = variables[keys[keynum]];\
		if(s.type == Types::INT || s.type == Types::SHORT || s.type == Types::MAX) {\
			dest = *((__VA_ARGS__ long long*) s.value);\
		} else {\
			std::cerr << "ERROR["+std::string(operation)+std::string("]: ")+std::string(#count)+std::string(" argument variable is not compatible with destination") << std::endl;\
			return 1;\
		}\
	} else if(isNumber(keys[keynum])) {\
		dest = atol(keys[keynum].c_str());\
	} else {\
		std::cerr << "ERROR["+std::string(operation)+std::string("]: ")+std::string(#count)+std::string(" argument is not a valid token") << std::endl;\
		return 1;\
	}

#define mathAutomator_switch(...) \
	switch (operation) {\
		case 0:\
			*((__VA_ARGS__ long long*) dest.value) = a1 + a2;\
			break;\
		case 1:\
			*((__VA_ARGS__ long long*) dest.value) = a1 - a2;\
			break;\
		case 2:\
			*((__VA_ARGS__ long long*) dest.value) = a1 * a2;\
			break;\
		case 3:\
			*((__VA_ARGS__ long long*) dest.value) = a1 / a2;\
			break;\
		case 4:\
			*((__VA_ARGS__ long long*) dest.value) = a1 % a2;\
			break;\
	}
bool mathAutomator(std::map<std::string, Variable> &variables, std::vector<std::string> keys, int operation, std::string operationText) {
	std::map<std::string, Variable>::iterator it = variables.find(keys[1]);
	std::map<std::string, Variable>::iterator it1 = variables.find(keys[2]);
	std::map<std::string, Variable>::iterator it2 = variables.find(keys[3]);
	if(it != variables.end()) {
		Variable dest = variables[keys[1]];
		if(dest.type == Types::INT || dest.type == Types::SHORT || dest.type == Types::MAX) {
			if(dest.isUnsigned) {
				unsigned long long a1;
				unsigned long long a2;

				mathAutomator_varCheck(it1, a1, 2, operationText, Second, unsigned);
				mathAutomator_varCheck(it2, a2, 3, operationText, Third, unsigned);

				mathAutomator_switch(unsigned);
			} else {
				signed long long a1;
				signed long long a2;

				mathAutomator_varCheck(it1, a1, 2, operationText, Second, signed);
				mathAutomator_varCheck(it2, a2, 3, operationText, Third, signed);

				mathAutomator_switch(signed);
			}
		} else {
			std::cerr << "ERROR["+ operationText +"]: Destination is not a number type" << std::endl;
			return 1;
		}
	} else {
		std::cerr << "ERROR["+ operationText +"]: Couldn't find desired destination" << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	std::cout << "Beware! What you're about to see is a WIP version of InterCC (InterC Compiled) language interpreter." << std::endl
	<< "This is not an InterC interpreter - an InterC to InterCC compiler will soon be in developement :D" << std::endl
	<< "We hope for this program to soon just be a part of a full InterC language interpreter. For now, let's be happy with what we have." << std::endl
	<< "Version 2020.1 WIP" << std::endl;

	if(argc < 2) {
		std::cerr << "InterCC Main Error: No program file specified!" << std::endl;
		return 1;
	}

	std::string path = argv[1];

	std::ifstream inputFileStream(path);
	if(!inputFileStream) {
		std::cerr << "InterCC Main Error: Specified file couldn't open! " << "(\"" << path << "\")" << std::endl
		<< "List of possible errors:" << std::endl
		<< "1. File does not exist." << std::endl
		<< "2. File is corrupt." << std::endl
		<< "3. File is set so it can't be read by the program." << std::endl;
		return 1;
	}

	std::string file(static_cast<std::stringstream const&>(std::stringstream() << inputFileStream.rdbuf()).str());
	std::istringstream ifile(file);

	std::string key;
	std::vector<std::string> keys;

	std::map<std::string, Variable> variables_new;

	while(ifile >> key) {
		if(key != ";") {
			keys.push_back(key);
		}
		else {
			if(keys[0] == "#") {}
			else if(keys[0] == "NEW") {
				bool isUnsigned = false;
				bool isPointer = false;
				bool created = false;

				if(keys.size() != 3) {
					std::cerr << "ERROR[NEW]: Invalid call!" << std::endl;
					return 1;
				}

				if(keys[2].length() < 3) {
					std::cerr << "ERROR[NEW]: Invalid variable type" << std::endl;
					return 1;
				}

				if(keys[2].at(0) == 'P') {
					keys[2] = keys[2].substr(1);
					isPointer = true;
				}
				if(keys[2].at(0) == 'U') {
					keys[2] = keys[2].substr(1);
					isUnsigned = true;
				}

				checkType(CHAR, char);
				checkType(INT, int);
				checkType(SHORT, short);
				checkType(MAX, long long);
			}
			else if(keys[0] == "DEL") {
				std::map<std::string, Variable>::iterator it = variables_new.find(keys[1]);
				if(it != variables_new.end()) {
					delete variables_new[keys[1]].value;
					variables_new.erase(it);
				} else {
					std::cerr << "ERROR[DEL]: Couldn't delete desired variable!" << std::endl;
					return 1;
				}
			}
			else if(keys[0] == "SET") {
				std::map<std::string, Variable>::iterator it = variables_new.find(keys[1]);
				if(it != variables_new.end()) {
					Variable var = variables_new[keys[1]];
					if(isNumber(keys[2])) {
						if(var.type == Types::INT || var.type == Types::SHORT || var.type == Types::MAX) {
							if(var.isUnsigned) {
								unsigned long long i = atol(keys[2].c_str());
								*((unsigned long long*) var.value) = i;
							} else {
								signed long long i = atol(keys[2].c_str());
								*((signed long long*) var.value) = i;
							}
						} else {
							std::cerr << "ERROR[SET]: Invalid value!" << std::endl;
							return 1;
						}
					}
				} else {
					std::cerr << "ERROR[SET]: Couldn't set desired variable!" << std::endl;
					return 1;
				}
			}
			else if(keys[0] == "ADD") {
				if(mathAutomator(variables_new, keys, 0, "ADD")) return 1;
			}
			else if(keys[0] == "SUB") {
				if(mathAutomator(variables_new, keys, 1, "SUB")) return 1;
			}
			else if(keys[0] == "MUL") {
				if(mathAutomator(variables_new, keys, 2, "MUL")) return 1;
			}
			else if(keys[0] == "DIV") {
				if(mathAutomator(variables_new, keys, 3, "DIV")) return 1;
			}
			else if(keys[0] == "MOD") {
				if(mathAutomator(variables_new, keys, 4, "MOD")) return 1;
			}
			else if(keys[0] == "PRINT") {
				for(unsigned int i = 1; i < keys.size(); i++) {
					if(isNumber(keys[i])) {
						std::cout << keys[i] << " ";
					} else {
						std::map<std::string, Variable>::iterator it = variables_new.find(keys[1]);
						if(it != variables_new.end()) {
							Variable var = variables_new[keys[i]];
							if(var.type == Types::INT || var.type == Types::SHORT || var.type == Types::MAX) {
								if(var.isUnsigned) {
									std::cout << *((unsigned long long*)var.value) << " ";
								} else {
									std::cout << *((signed long long*)var.value) << " ";
								}
							} else {
								std::cerr << "ERROR[PRINT]: Invalid variable!" << std::endl;
								return 1;
							}
						} else {
							std::cerr << "ERROR[PRINT]: Couldn't print desired variable!" << std::endl;
							return 1;
						}
					}
				}
				std::cout << std::endl;
			}

			keys.clear();
		}
	}

	return 0;
}
