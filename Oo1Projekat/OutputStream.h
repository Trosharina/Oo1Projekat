#pragma once
#include <string>

using namespace std;

class OutputStream
{
public:
	virtual void put(char c) = 0;
	virtual ~OutputStream() = default;
	void write(const string& str);
};

