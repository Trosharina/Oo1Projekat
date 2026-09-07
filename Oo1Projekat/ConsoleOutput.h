#pragma once
#include "OutputStream.h"

class ConsoleOutput : public OutputStream
{
public:
	void put(char c) override;
};

