#pragma once
#include <string>
#include "InputStream.h"

using namespace std;

class ConsoleInput : public InputStream
{
public:
	ConsoleInput();
	char get() override;
	bool eof() const override;
private:
	string buffer;
	size_t pos = 0;
};

