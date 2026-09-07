#pragma once
#include "Command.h"

class Batch : public Command
{
public:
	void execute(InputStream& in, OutputStream& out, Interpreter& interp) override;
	void setArgument(const string& arg) override;
	bool needsInput() const override;
private:
	string filename;
};

