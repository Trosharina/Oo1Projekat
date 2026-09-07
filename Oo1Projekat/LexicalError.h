#pragma once
#include "InterpreterError.h"
#include <vector>

class LexicalError : public InterpreterError
{
public:
	LexicalError(const string& msg, const vector<size_t>& pos, const string& line);
	const vector<size_t>& getPosition() const;
	const string& getLine() const;
	string format() const;
private:
	string line;
	vector<size_t> positions;
};

