#include "Truncate.h"
#include <fstream>
#include "FileError.h"

void Truncate::execute(InputStream& input, OutputStream& output, Interpreter&) {
	ifstream check(filename);
	if (!check.good())
		throw FileError("truncate: file does not exist: " + filename);
	check.close();
	
	ofstream file(filename, ios::trunc);
	if (!file.is_open())
		throw FileError("truncate: cannot open file: " + filename);
}

void Truncate::setArgument(const string& argument) {
	filename = argument;
}

bool Truncate::needsInput() const {
	return false;
}