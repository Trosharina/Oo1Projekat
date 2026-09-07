#include "Tr.h"
#include "SyntaxError.h"
#include "CommandError.h"

void Tr::setRawTokens(const vector<Token>& tokens) {
	size_t idx = 1;

	if (idx < tokens.size() && (tokens[idx].type == Token::QUOTED || (tokens[idx].type == Token::WORD && tokens[idx].text != "-")))
		idx++;

	if (idx >= tokens.size() || tokens[idx].type != Token::WORD || tokens[idx].text != "-") {
		throw SyntaxError("tr: expected '-' before pattern", 0);
	}
	idx++;

	if (idx >= tokens.size() || tokens[idx].type != Token::QUOTED) {
		throw SyntaxError("tr: expected quoted pattern", 0);
	}
	what = tokens[idx++].text;

	if (idx < tokens.size() && tokens[idx].type == Token::QUOTED) {
		with = tokens[idx++].text;
	}
	parsed = true;
}

void Tr::execute(InputStream& in, OutputStream& out, Interpreter&) {
	if (!parsed || what.empty())
		throw CommandError("tr: missing pattern");
	
	string input;
	while (!in.eof())
		input += in.get();

	string result;
	size_t pos = 0;
	while (pos < input.size()) {
		if (input.compare(pos, what.size(), what) == 0) {
			result += with;
			pos += what.size();
		}
		else {
			result += input[pos++];
		}
	}
	out.write(result);
}