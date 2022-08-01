#include "Compiler.h"
#include <sstream>

std::string Compiler::compile(const Args args, const std::string& body) {
	std::string assembly;
	this->args = args;

	assembly += header();

	assembly += body;

	assembly += footer();

	return assembly;
}

std::string Compiler::header() {
	std::stringstream ss;
	ss << "includelib ../lib/kernel32.lib\n\n";

	if (args.includePrint or args.includeRead) {
		ss << "GetStdHandle proto\n";
	}
	if (args.includePrint) {
		ss << "WriteConsoleA proto\n"
		   << "Console equ -11\n";
	}
	if (args.includeRead) {
		ss << "ReadConsoleA proto\n"
		   << "Keyboard equ -10\n";
	}

	ss << "ExitProcess proto\n"
	   << "\n"
	   << ".code\n"
	   << "main proc\n"
	   << "\tsub RSP, 40 ; shadow space\n"
	   << "\n";

	if (args.includePrint) {
		ss << "\tmov RCX, Console\n"
		   << "\tcall GetStdHandle\n"
		   << "\tmov stdout, RAX\n\n";
	}

	if (args.includeRead) {
		ss << "\tmov RCX, Keyboard\n"
		   << "\tcall GetStdHandle\n"
		   << "\tmov stdin, RAX\n\n";
	}

	ss << "\tlea RBX, arr\n\n";

	return ss.str();
}

std::string Compiler::footer() {
	std::stringstream ss;
	ss <<
		"\tadd RSP, 40 ; release shadow space\n"
		"\tmov RCX, 0 ; clear RCX\n"
		"\tmov CL, [RBX]\n"
		"\tcall ExitProcess\n"
		"\n"
		"main endp\n"
		"\n"
		".data\n";

	if (args.includePrint) {
		ss << "\tnbwr QWORD ?\n"
			  "\tstdout QWORD ?\n";
	}

	if (args.includeRead) {
		ss << "\tnbrd QWORD ?\n"
		   << "\tstdin QWORD ?\n"
		   << "\tkeymsg BYTE 3 DUP (?)\n";
	}

	ss << "\tMaxBuf equ " << std::to_string(args.memSize) << "\n";

	ss << 
		"\tarr BYTE MaxBuf DUP (0)\n"
		"\n"
		"end";

	return ss.str();
}