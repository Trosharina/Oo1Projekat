#pragma once
#include "OutputStream.h"
#include <fstream>

class FileOutput : public OutputStream
{
public:
	FileOutput(const string& filename, bool append = false);
	void put(char c) override;
private:
	ofstream file;
};

