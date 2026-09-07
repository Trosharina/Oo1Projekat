#include "Head.h"
#include "CommandError.h"

void Head::execute(InputStream& in, OutputStream& out, Interpreter& interp) {
	if (option.size() < 3 || option[0] != '-' || option[1] != 'n')
		throw CommandError("head: invalid option: " + option);

	string digits = option.substr(2);
	if (digits.size() > 5)
		throw CommandError("head: line count to long: " + digits);

	for (char c : digits) {
		if (!isdigit(static_cast<unsigned char>(c)))
			throw CommandError("head: invalid line count: " + digits);
	}

	int count = stoi(digits);
	int lineSeens = 0;

	while (!in.eof() && lineSeens < count) {
		char c = in.get();
		out.put(c);
		if (c == '\n')
			++lineSeens;
	}
}

void Head::setOption(const string& opt) {
	option = opt;
}