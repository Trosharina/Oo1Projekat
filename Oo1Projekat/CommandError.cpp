#include "CommandError.h"

CommandError::CommandError(const string& msg)
	: InterpreterError(msg) { }