#pragma once
#include "OutputStream.h"

class StringOutput : public OutputStream
{
public:
	void put(char c) override;
	const string& getBuffer() const;
private:
	string buffer;
};

