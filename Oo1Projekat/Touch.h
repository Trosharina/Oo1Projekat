#pragma once
#include "Command.h"

class Touch : public Command
{
public:
	void execute(InputStream& input, OutputStream& output, Interpreter&) override;
	void setArgument(const string& argument) override;
	bool needsInput() const override;
private:
	string filename;
};

