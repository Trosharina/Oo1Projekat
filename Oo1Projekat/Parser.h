#pragma once
#include <string>
#include <vector>

using namespace std;

enum ArgType {
	NONE,
	QUOTED,
	FILENAME
};

struct Token {
	enum Type {
		WORD,
		QUOTED,
		PIPE,
		REDIRECT_IN,
		REDIRECT_OUT,
		APPEND
	} type = WORD; 
	string text;
	size_t position = 0;
};

struct ParsedCommand {
	string name;
	string option;
	string argument;
	ArgType argType = NONE;

	string inputRedirect;
	string outputRedirect;
	bool appendOutput = false;

	vector<Token> rawTokens;
};

struct CommandLine {
	vector<ParsedCommand> commands;
};

class Parser
{
public:
	CommandLine parse(const string& input) const;
private:
	vector<Token> tokenize(const string& input) const;
	size_t emitOperator(const string& input, size_t i, vector<Token>& tokens) const;
	vector<size_t> findIllegalCharacters(const string& input) const;
	vector<vector<Token>> splitByPipe(const vector<Token>& tokens) const;
	ParsedCommand interpretGroup(const vector<Token>& tokens) const;
};

