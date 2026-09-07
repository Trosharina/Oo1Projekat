#pragma once
#include "Command.h"

class Rm : public Command
{
public:
	void execute(InputStream& in, OutputStream& out, Interpreter&) override;
	void setArgument(const string& argument) override;
	bool needsInput() const override;
private:
	string filename;
};

