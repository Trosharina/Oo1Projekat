#include "Wc.h"
#include "CommandError.h"

void Wc::execute(InputStream& input, OutputStream& output, Interpreter&) {
	if (option == "-c") {
		countChars(input, output);
	}
	else if (option == "-w") {
		countWords(input, output);
	}
	else {
		throw CommandError("wc: ivalid or missing option:" + option);
	}
}

void Wc::setOption(const string& opt) {
	option = opt;
}

void Wc::countChars(InputStream& input, OutputStream& output) {
	long count = 0;
	while (!input.eof()) {
		input.get();
		++count;
	}
	output.write(to_string(count));
}

void Wc::countWords(InputStream& input, OutputStream& output) {
	long count = 0;
	bool inWord = false;

	while (!input.eof()) {
		char c = input.get();
		if (isspace(static_cast<unsigned char>(c))) {
			inWord = false;
		}
		else if (!inWord) {
			inWord = true;
			++count;
		}
	}

	output.write(to_string(count));
}