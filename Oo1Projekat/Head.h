#pragma once
#include "Command.h"
class Head : public Command
{
public:
	void execute(InputStream& in, OutputStream& out, Interpreter&) override;
	void setOption(const string& option) override;
private:
	string option;
	int lineCount = 0;
};

