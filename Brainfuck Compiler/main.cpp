#include <stdio.h>
#include <fstream>
#include "Instructions.h"
#include "Interpreter.h"
#include "Compiler.h"

bool validArguments(int argc, const char* argv[]);
Instructions readFile(const char* filename);
bool writeFile(const char* filename, const std::string& data);
void errorBadFile(const char* filename);
void assembleAndLink();
bool isNumber(const std::string& s);

int main(int argc, const char* argv[]) {
	// validate command line input
	if (!validArguments(argc, argv)) {
		return 1;
	}

	// read and parse file
	Instructions instructions = readFile(argv[1]);

	// if errors occurred in parsing then we can end early
	if (!instructions.isValid()) {
		printf("Compilation failed parsing\n");
		return 1;
	}

	// go through operations and create IL
		// just covnerts each instruction directly to assmebly atm
	Interpreter interpreter(&instructions);
	Compiler compiler;

	Compiler::Args compilerArgs;
	if (argc > 2) compilerArgs.memSize = std::stoull(argv[2]);
	compilerArgs.includePrint = instructions.prints();
	compilerArgs.includeRead  = instructions.reads();

	if (!writeFile("main.asm", compiler.compile(compilerArgs, interpreter.interpret()))) {
		printf("Compilation failed to write to output file\n");
	}

	assembleAndLink();

	return 0;
}

bool validArguments(int argc, const char* argv[]) {
	bool isValid = true;

	if (argc < 2) isValid = false; // no file specified
	if (argc > 2 and !isNumber(argv[2])) isValid = false; // memSize arg is not a number

	return isValid;
}

Instructions readFile(const char* filename) {
	Instructions instructions;

	std::ifstream file(filename);
	if (!file.is_open()) {
		errorBadFile(filename);
		return instructions;
	}

	size_t lineNumber = 0;
	size_t indexOfFirst = 0;
	char c;
	while (file.get(c)) {
		if (c == '\n') {
			lineNumber++;
			indexOfFirst = file.tellg();
		}
		else if (!instructions.addInstruction(c)) {
			printf("Error in parsing: %s, (%llu, %llu)\n", filename, lineNumber, (size_t)file.tellg() - indexOfFirst - 1);
		}
	}

	file.close();

	return instructions;
}

bool writeFile(const char* filename, const std::string& data) {
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		errorBadFile(filename);
		return false;
	}

	file << data;

	file.close();

	return true;
}

void errorBadFile(const char* filename) {
	printf("[Error] Unable to open file: %s\n", filename);
}

void assembleAndLink() {
	printf("assembling: ret (%d)\n", system("cd asm_link && ml64.exe ../main.asm /link /SUBSYSTEM:CONSOLE /ENTRY:main && move main.exe ../main.exe & cd .."));
}

bool isNumber(const std::string& s){
	std::string::const_iterator it = s.begin();

	while (it != s.end() && std::isdigit(*it)) ++it;

	try {
		std::stoull(s);
	}
	catch (...) {
		return false;
	}

	return !s.empty() && it == s.end();
}