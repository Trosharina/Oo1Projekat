#pragma once
#include "Command.h"

class Echo : public Command
{
public:
	void execute(InputStream& input, OutputStream& output, Interpreter&) override;
};

