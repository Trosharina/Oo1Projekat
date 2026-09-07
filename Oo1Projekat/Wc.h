#pragma once
#include "Command.h"

class Wc : public Command
{
public:
	void execute(InputStream& input, OutputStream& output, Interpreter&) override;
	void setOption(const string& option) override;
private:
	string option;
	void countChars(InputStream& input, OutputStream& output);
	void countWords(InputStream& input, OutputStream& output);
};

