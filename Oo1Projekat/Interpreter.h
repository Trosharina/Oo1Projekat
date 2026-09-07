#pragma once
#include <string>
#include "Parser.h"
#include "CommandFactory.h"

using namespace std;

class Interpreter
{
public:
	void run();
	void setPrompt(const string& prompt);
	void executeLineSafely(const string& line);
private:
	string prompt = "$";
	Parser parser;
	CommandFactory commandFactory;

	void executeLine(const string& line);
	void executeSingle(const ParsedCommand& pc);
	void executePipe(const vector<ParsedCommand>& pcs);
	void validatePipe(const vector<ParsedCommand>& pcs) const;
	unique_ptr<InputStream> makeInput(const ParsedCommand& pc, const Command& command) const;
	unique_ptr<OutputStream> makeOutput(const ParsedCommand& pc) const;
};

