#include "Interpreter.h"
#include <sstream>

Interpreter::Interpreter(Instructions* instructions) {
	this->instructions = instructions;
}

std::string Interpreter::interpret() {
	std::string assembly;
	while (instructions->hasNext()) {
		Operation op = instructions->next();
		if (op != Operation::INVALID) {
			assembly += translateOperation(op);
		}
	}
	return assembly;
}

std::string Interpreter::translateOperation(Operation op) {
	if (op == Operation::INC)        return "\tinc BYTE PTR [RBX]\n";
	else if (op == Operation::DEC)   return "\tdec BYTE PTR [RBX]\n";
	else if (op == Operation::RIGHT) return "\tinc RBX\n";
	else if (op == Operation::LEFT)  return "\tdec RBX\n";
	else if (op == Operation::LOOP_START) {
		loops.push(loopCount);

		std::stringstream ss;
		ss << "l" << std::to_string(loopCount) << ":\n";
		ss << "\tcmp BYTE PTR[RBX], 0\n";
		ss << "\tjz e" << std::to_string(loopCount) << "\n";

		loopCount++;

		return ss.str();
	}
	else if (op == Operation::LOOP_END) {
		size_t loopNum = loops.top();
		loops.pop();

		std::stringstream ss;
		ss << "\tjmp l" << std::to_string(loopNum) << "\n\n";
		ss << "e" << std::to_string(loopNum) << ":\n";

		return ss.str();
	}
	else if (op == Operation::PRINT) {
		std::stringstream ss;
		ss << "\n\tmov RCX, stdout\n"
		   << "\tlea RDX, BYTE PTR [RBX]\n"
		   << "\tmov R8, 1\n"
		   << "\tlea R9, nbwr\n"
		   << "\tcall WriteConsoleA\n\n";

		return ss.str();
	}
	else if (op == Operation::READ) {
		std::stringstream ss;
		ss  << "\n\tmov RCX, stdin\n"
			<< "\tlea RDX, keymsg\n"
			<< "\tmov R8, 3\n"
			<< "\tlea R9, nbrd\n"
			<< "\tcall ReadConsoleA\n\n"
			<< "\tmov R12B, BYTE PTR [keymsg]\n"
			<< "\tmov [RBX], R12B\n\n";

		return ss.str();
	}

	return "";
}