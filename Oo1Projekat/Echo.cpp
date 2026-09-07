#include "Echo.h"

void Echo::execute(InputStream& input, OutputStream& output, Interpreter&) {
	while (!input.eof()) {
		output.put(input.get());
	}
}