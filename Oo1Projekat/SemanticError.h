#pragma once
#include "InterpreterError.h"
class SemanticError : public InterpreterError 
{
public:
	SemanticError(const string& msg);
};

