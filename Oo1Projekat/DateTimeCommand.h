#pragma once
#include "Command.h"

class DateTimeCommand : public Command
{
public:
	void execute(InputStream& input, OutputStream& output, Interpreter&) override;
	bool needsInput() const override;
protected:
	virtual string getFormat() const = 0;
};

