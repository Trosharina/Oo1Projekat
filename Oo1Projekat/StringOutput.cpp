#include "StringOutput.h"

void StringOutput::put(char c) {
	buffer += c;
}

const string& StringOutput::getBuffer() const {
	return buffer;
}