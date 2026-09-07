#include "LexicalError.h"

LexicalError::LexicalError(const string& message, const vector<size_t>& pos, const string& line)
	: InterpreterError(message), positions(pos), line(line) { }

const vector<size_t>& LexicalError::getPosition() const {
	return positions;
}

const string& LexicalError::getLine() const {
	return line;
}

string LexicalError::format() const {
	string result = "Error - ";
	result += what();
	result += "\n";
	result += line;
	result += "\n";

	string marker(line.size(), ' ');
	for (size_t pos : positions) {
		if (pos < marker.size()) {
			marker[pos] = '^';
		}
	}
	result += marker;

	return result;
}