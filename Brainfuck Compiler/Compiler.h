#pragma once
#include <string>

class Compiler
{
public:
	struct Args {
		size_t memSize = 2048;
		bool includePrint = false;
		bool includeRead = false;
	};

private:
	Args args;

public:
	Compiler() {}
	~Compiler() {}

	std::string compile(const Args args, const std::string& body);

private:
	std::string header();
	std::string footer();
};

