#pragma once
#include <stack>
#include <string>
#include "Instructions.h"

class Interpreter
{
private:
	size_t loopCount = 0;
	std::stack<size_t> loops;
	Instructions* instructions;

public:
	Interpreter(Instructions* instructions);
	~Interpreter() {}

	std::string interpret();

private:
	std::string translateOperation(Operation op);
};

