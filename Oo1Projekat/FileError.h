#pragma once
#include "InterpreterError.h"

class FileError : public InterpreterError
{
public:
	FileError(const string& msg);
};

