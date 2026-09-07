#include "DateTimeCommand.h"
#include <ctime>

void DateTimeCommand::execute(InputStream& input, OutputStream& output, Interpreter&) {
	time_t now = time(nullptr);
	tm local;
	localtime_s(&local, &now);

	char buffer[64];
	strftime(buffer, sizeof(buffer), getFormat().c_str(), &local);
	output.write(buffer);
}

bool DateTimeCommand::needsInput() const {
	return false;
}