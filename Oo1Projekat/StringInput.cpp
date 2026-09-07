#include "StringInput.h"

StringInput::StringInput(const string& s)
	: data(s), pos(0) { }

char StringInput::get() {
	return data[pos++];
}

bool StringInput::eof() const {
	return pos >= data.size();
}