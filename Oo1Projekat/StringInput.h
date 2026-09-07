#pragma once
#include "InputStream.h"
#include <string>

using namespace std;

class StringInput : public InputStream
{
public:
	StringInput(const string& s);

	char get() override;
	bool eof() const override;

private:
	string data;
	size_t pos;
};

