#pragma once
#include "Command.h"

class Prompt : public Command
{
public:
	void execute(InputStream& in, OutputStream& out, Interpreter& interp) override;
	void setArgument(const string& argument) override;
	bool needsInput() const override;
private:
	string newPrompt;
};

