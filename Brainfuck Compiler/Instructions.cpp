#include "Instructions.h"
#include <stdio.h>

void errorUnexpectedToken(char c);

Instructions::Instructions() {
}

Instructions::Instructions(Instructions&& other) noexcept{
	instructions = other.instructions;
	other.instructions.clear();

	pos = other.pos;
	other.pos = 0;

	loopDepth = other.loopDepth;
	other.loopDepth = 0;

	valid = other.valid;
	other.valid = false;

	usesPrint = other.usesPrint;
	other.usesPrint = false;

	usesRead = other.usesRead;
	other.usesRead = false;
}

Instructions::~Instructions() {
	instructions.clear();
}

// false means an error occured
bool Instructions::addInstruction(char c) {
	Operation operation = getOperation(c);
	if (operation == Operation::INVALID) return true;
	else if (operation == Operation::LOOP_START) loopDepth++;
	else if (operation == Operation::LOOP_END) {
		if (loopDepth > 0) {
			loopDepth--;
		}
		else {
			valid = false;
			errorUnexpectedToken(']');
			return false;
		}
	}
	else if (operation == Operation::PRINT) usesPrint = true;
	else if (operation == Operation::READ)  usesRead = true;

	instructions.push_back(operation);

	//printf("token: %c\n", c);

	return true;
}

bool Instructions::hasNext() const {
	return pos < instructions.size();
}

Operation Instructions::next() {
	if (hasNext()) {
		return instructions[pos++];
	}
	return Operation::INVALID;
}

bool Instructions::isValid() const {
	return valid and !empty();
}

bool Instructions::empty() const {
	return instructions.size() == 0;
}

bool Instructions::prints() const {
	return usesPrint;
}

bool Instructions::reads() const {
	return usesRead;
}

Operation Instructions::getOperation(const char c) const {
	switch (c) {
	case '+': return Operation::INC;
	case '-': return Operation::DEC;
	case '<': return Operation::LEFT;
	case '>': return Operation::RIGHT;
	case '[': return Operation::LOOP_START;
	case ']': return Operation::LOOP_END;
	case '.': return Operation::PRINT;
	case ',': return Operation::READ;
	default : return Operation::INVALID;
	}
}

void errorUnexpectedToken(char c) {
	printf("[Syntax Error] encountered unexpected token '%c'\n", c);
}
