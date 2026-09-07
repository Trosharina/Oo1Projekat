#include "Touch.h"
#include "FileError.h"
#include <fstream>

void Touch::execute(InputStream& input, OutputStream& output, Interpreter&) {
	ifstream check(filename);
	if (check.good()) {
		throw FileError("Touch: file already exists: " + filename);
	}
	check.close();

	ofstream create(filename);
	if (!create.is_open()) {
		throw FileError("Touch: cannot create file: " + filename);
	}
}

void Touch::setArgument(const string& argument) {
	filename = argument;
}

bool Touch::needsInput() const {
	return false;
}