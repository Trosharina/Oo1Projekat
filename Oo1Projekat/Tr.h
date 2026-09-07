#pragma once
#include "Command.h"

class Tr : public Command
{
public:
	void execute(InputStream& in, OutputStream& out, Interpreter&) override;
	void setRawTokens(const vector<Token>& tokens) override;
private:
	string what;
	string with;
	bool parsed = false;
};

