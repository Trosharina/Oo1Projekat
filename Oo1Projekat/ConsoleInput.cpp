#include "ConsoleInput.h"
#include <iostream>

ConsoleInput::ConsoleInput() {
	int c;
	while ((c = cin.get()) != EOF)
		buffer += static_cast<char>(c);
}

char ConsoleInput::get() {
	return buffer[pos++];
}

bool ConsoleInput::eof() const {
	return pos >= buffer.size();
}