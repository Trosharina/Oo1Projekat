#pragma once
#include "InputStream.h"
#include "OutputStream.h"
#include <vector>
#include "Parser.h"

class Interpreter;

class Command
{
public:
	virtual void execute(InputStream& input, OutputStream& output, Interpreter& interp) = 0;
	virtual void setOption(const string& option);
	virtual void setArgument(const string& argument);
	virtual bool needsInput() const;
	virtual void setRawTokens(const vector<Token>& tokens);
	virtual ~Command() = default;
};
