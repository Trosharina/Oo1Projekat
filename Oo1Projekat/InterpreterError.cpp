#include "InterpreterError.h"

InterpreterError::InterpreterError(const string& msg)
	: message(msg) { }

const string& InterpreterError::what() const {
	return message;
}