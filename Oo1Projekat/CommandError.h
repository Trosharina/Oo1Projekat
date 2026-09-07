#pragma once
#include "InterpreterError.h"

class CommandError : public InterpreterError
{
public:
	CommandError(const string& msg);
};

