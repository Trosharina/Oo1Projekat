#include "FileOutput.h"
#include "FileError.h"

FileOutput::FileOutput(const string& filename, bool append)
	: file(filename, append ? ios::app : ios::trunc) {
	if (!file.is_open()) {
		throw FileError("Cannot open file: " + filename);
	}
}

void FileOutput::put(char c) {
	file << c;
}