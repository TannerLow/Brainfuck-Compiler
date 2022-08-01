#pragma once
#include <vector>
#include "Operation.h"

class Instructions
{
private:
	std::vector<Operation> instructions;
	size_t pos = 0;
	size_t loopDepth = 0;
	bool valid = true;
	bool usesPrint = false;
	bool usesRead = false;

public:
	Instructions();
	Instructions(Instructions&& other) noexcept;
	~Instructions();

	bool addInstruction(const char c);
	bool hasNext() const;
	Operation next();
	bool isValid() const;
	bool empty() const;
	bool prints() const;
	bool reads() const;

private:
	Operation getOperation(const char c) const;
};

