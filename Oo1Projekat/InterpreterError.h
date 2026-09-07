#pragma once
#include <string>

using namespace std;

class InterpreterError
{
public:
	InterpreterError(const string& msg);

	const string& what() const;
	virtual ~InterpreterError() = default;
private:
	string message;
};

