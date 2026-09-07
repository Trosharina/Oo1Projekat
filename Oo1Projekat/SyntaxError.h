#pragma once
#include "InterpreterError.h"

class SyntaxError : public InterpreterError
{
public:
	SyntaxError(const string& msg, size_t pos);
	size_t getPosition() const;
private:
	size_t position;
};

