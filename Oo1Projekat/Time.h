#pragma once
#include "DateTimeCommand.h"

class Time : public DateTimeCommand
{
protected:
	string getFormat() const override;
};

