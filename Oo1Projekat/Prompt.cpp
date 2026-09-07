#include "Prompt.h"
#include "Interpreter.h"

void Prompt::execute(InputStream& in, OutputStream& out, Interpreter& interp) {
	interp.setPrompt(newPrompt);
}

void Prompt::setArgument(const string& argument) {
	newPrompt = argument;
}

bool Prompt::needsInput() const {
	return false;
}