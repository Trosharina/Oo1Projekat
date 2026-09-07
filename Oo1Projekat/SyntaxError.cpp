#include "SyntaxError.h"

SyntaxError::SyntaxError(const string& msg, size_t pos)
	: InterpreterError(msg), position(pos) { }

size_t SyntaxError::getPosition() const {
	return position;
}