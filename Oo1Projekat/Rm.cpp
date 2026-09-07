#include "Rm.h"
#include "FileError.h"

void Rm::execute(InputStream& in, OutputStream& out, Interpreter&) {
	if (remove(filename.c_str()) != 0) {
		throw FileError("rm: cannot remove file: " + filename);
	}
}

void Rm::setArgument(const string& argument) {
	filename = argument;
}

bool Rm::needsInput() const {
	return false;
}