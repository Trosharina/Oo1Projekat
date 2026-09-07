#pragma once
#include "DateTimeCommand.h"

class Date : public DateTimeCommand
{
protected:
	string getFormat() const override;
};

