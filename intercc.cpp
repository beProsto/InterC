#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>

enum Types {
	CHAR = 0,
	UCHAR = 1,
	PCHAR = 2,
	PUCHAR = 3,
	INT = 4,
	UINT = 5,
	PINT = 6,
	PUINT = 7,
	MAX = 8,
	UMAX = 9,
	PMAX = 10,
	PUMAX = 11,
	PTR = 12
};

bool isNumber(char _c) {
	return _c == '0' || _c == '1' || _c == '2' || _c == '3' || _c == '4' || _c == '5' || _c == '6' || _c == '7' || _c == '8' || _c == '9' || _c == '-';
}
bool isNumber(const std::string& _s) {
	return isNumber(_s[0]);
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

	std::map<std::string, int> variables;

	while(ifile >> key) {
		if(key != ";") {
			keys.push_back(key);
		}
		else {
			if(keys[0] == "#") {}
			else if(keys[0] == "NEW") {
				variables[keys[1]] = 0;
			}
			else if(keys[0] == "DEL") {
				variables.erase(variables.find(keys[1]));
			}
			else if(keys[0] == "SET") {
				variables.find(keys[1])->second = (isNumber(keys[2]) ? std::stoi(keys[2]) : variables.find(keys[2])->second);
			}
			else if(keys[0] == "ADD") {
				variables.find(keys[1])->second = 
				(isNumber(keys[2][0]) ? std::stoi(keys[2]) : variables.find(keys[2])->second) + 
				(isNumber(keys[3][0]) ? std::stoi(keys[3]) : variables.find(keys[3])->second);
			}
			else if(keys[0] == "SUB") {
				variables.find(keys[1])->second = 
				(isNumber(keys[2]) ? std::stoi(keys[2]) : variables.find(keys[2])->second) - 
				(isNumber(keys[3]) ? std::stoi(keys[3]) : variables.find(keys[3])->second);
			}
			else if(keys[0] == "MUL") {
				variables.find(keys[1])->second = 
				(isNumber(keys[2]) ? std::stoi(keys[2]) : variables.find(keys[2])->second) * 
				(isNumber(keys[3]) ? std::stoi(keys[3]) : variables.find(keys[3])->second);
			}
			else if(keys[0] == "DIV") {
				variables.find(keys[1])->second = 
				(isNumber(keys[2]) ? std::stoi(keys[2]) : variables.find(keys[2])->second) / 
				(isNumber(keys[3]) ? std::stoi(keys[3]) : variables.find(keys[3])->second);
			}
			else if(keys[0] == "MOD") {
				variables.find(keys[1])->second = 
				(isNumber(keys[2]) ? std::stoi(keys[2]) : variables.find(keys[2])->second) % 
				(isNumber(keys[3]) ? std::stoi(keys[3]) : variables.find(keys[3])->second);
			}
			else if(keys[0] == "PRINT") {
				for(unsigned int i = 1; i < keys.size(); i++) {
					std::cout << (isNumber(keys[i]) ? std::stoi(keys[i]) : variables.find(keys[i])->second) << " ";
				}
				std::cout << std::endl;
			}

			keys.clear();
		}
	}
	return 0;
}
