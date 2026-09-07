#include "FileInput.h"
#include "FileError.h"

FileInput::FileInput(const string& filename)
	: file(filename) {
	if (!file.is_open())
		throw FileError("Cannot open file: " + filename);
	nextChar = file.get();
}

char FileInput::get() {
	char c = static_cast<char>(nextChar);
	nextChar = file.get();
	return c;
}

bool FileInput::eof() const {
	return nextChar == EOF;
}