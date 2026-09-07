#pragma once
#include "InputStream.h"
#include <fstream>

using namespace std;

class FileInput : public InputStream
{
public:
	FileInput(const string& filename);

	char get() override;
	bool eof() const override;
private:
	ifstream file;
	int nextChar;
};

