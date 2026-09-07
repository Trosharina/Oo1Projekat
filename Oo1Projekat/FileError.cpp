#include "FileError.h"

FileError::FileError(const string& msg)
	: InterpreterError(msg) {}