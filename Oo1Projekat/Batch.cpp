#include "Batch.h"
#include "FileError.h"
#include "Interpreter.h"
#include <fstream>

void Batch::execute(InputStream& in, OutputStream& out, Interpreter& interp) {
	ifstream file(filename);
	if (!file.is_open()) {
		throw FileError("batch: cannot open file: " + filename);
	}
	string line;
	while (getline(file, line)) {
		interp.executeLineSafely(line);
	}
}

void Batch::setArgument(const string& argument) {
	filename = argument;
}

bool Batch::needsInput() const {
	return false;
}