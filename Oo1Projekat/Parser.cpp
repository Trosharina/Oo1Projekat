#include "Parser.h"
#include "LexicalError.h"
#include "SyntaxError.h"
#include "SemanticError.h"

static bool isAllowedChar(char c) {
	if (isalnum(static_cast<unsigned char>(c))) return true;
	static const string allowed = "-_./\\:~";
	return allowed.find(c) != string::npos;
}

vector<Token> Parser::tokenize(const string& input) const {
	vector<Token> tokens;

	enum State {
		SKIP_WHITESPACE,
		READING_WORD,
		READING_QUOTED
	};
	State state = SKIP_WHITESPACE;
	Token current;

	for (size_t i = 0; i < input.size(); ++i) {
		char c = input[i];

		switch (state) {
		case SKIP_WHITESPACE: 
			if (c == ' ' || c == '\t')
				continue;
			else if (c == '"') {
				current = Token{};
				current.type = Token::QUOTED;
				current.position = i;
				state = READING_QUOTED;
			}
			else if (c == '|' || c == '<' || c == '>') {
				i = emitOperator(input, i, tokens);
			}
			else {
				current = Token{};
				current.type = Token::WORD;
				current.text += c;
				state = READING_WORD;
			}
			break;
		case READING_WORD:
			if (c == ' ' || c == '\t') {
				tokens.push_back(current);
				state = SKIP_WHITESPACE;
			}
			else if (c == '"') {
				tokens.push_back(current);
				current = Token{};
				current.type = Token::QUOTED;
				current.position = i;
				state = READING_QUOTED;
			}
			else if (c == '|' || c == '<' || c == '>') {
				tokens.push_back(current);
				state = SKIP_WHITESPACE;
				i = emitOperator(input, i, tokens);
			}
			else {
				current.text += c;
			}
			break;
		case READING_QUOTED:
			if (c == '"') {
				tokens.push_back(current);
				state = SKIP_WHITESPACE;
			}
			else {
				current.text += c;
			}
			break;
		}
	}

	if (state == READING_WORD) {
		tokens.push_back(current);
	}
	else if (state == READING_QUOTED) {
		throw LexicalError("Untermited quote", vector<size_t>{current.position}, input);
	}

	return tokens;
}

CommandLine Parser::parse(const string& input) const {
	vector<size_t> illegal = findIllegalCharacters(input);
	if (!illegal.empty()){
		throw LexicalError("Unexpected characters", illegal, input);
	}

	vector<Token> tokens = tokenize(input);

	CommandLine result;
	if (tokens.empty())
		return result;

	vector<vector<Token>> groups = splitByPipe(tokens);
	for (const vector<Token>& group : groups) {
		result.commands.push_back(interpretGroup(group));
	}

	return result;
}

size_t Parser::emitOperator(const string& input, size_t i, vector<Token>& tokens) const {
	Token op;
	op.position = i;

	if (input[i] == '|') {
		op.type = Token::PIPE;
	}
	else if (input[i] == '<') {
		op.type = Token::REDIRECT_IN;
	}
	else {
		if (i + 1 < input.size() && input[i + 1] == '>') {
			op.type = Token::APPEND;
			++i;
		}
		else {
			op.type = Token::REDIRECT_OUT;
		}
	}
	tokens.push_back(op);
	return i;
}

vector<size_t> Parser::findIllegalCharacters(const string& input) const {
	vector<size_t> bad;
	bool inQuotes = false;

	for (size_t i = 0; i < input.size(); ++i) {
		char c = input[i];

		if (c == '"') { inQuotes = !inQuotes; continue; }

		if (inQuotes) continue;

		if (c == ' ' || c == '\t') continue;
		if (c == '|' || c == '<' || c == '>') continue;

		if (!isAllowedChar(c)) bad.push_back(i);
	}
	return bad;
}

vector<vector<Token>> Parser::splitByPipe(const vector<Token>& tokens) const {
	vector<vector<Token>> groups;
	vector<Token> current;

	for (const Token& t : tokens) {
		if (t.type == Token::PIPE) {
			if (current.empty()) {
				throw SyntaxError("Empty command in pipe", t.position);
			}
			groups.push_back(current);
			current.clear();
		}
		else {
			current.push_back(t);
		}
	}

	if (current.empty() && !groups.empty()) {
		throw SyntaxError("empty command at end of pipe", 0);
	}
	if (!current.empty()) {
		groups.push_back(current);
	}

	return groups;
}

ParsedCommand Parser::interpretGroup(const vector<Token>& tokens) const {
	ParsedCommand cmd;

	if (tokens.empty()) {
		throw SyntaxError("Empty command", 0);
	}

	size_t idx = 0;
	cmd.name = tokens[idx++].text;
	cmd.rawTokens = tokens;

	if (cmd.name == "tr") {
		size_t idx = 1;

		if (idx < tokens.size() && (tokens[idx].type == Token::QUOTED || (tokens[idx].type == Token::WORD && tokens[idx].text != "-"))) {
			cmd.argument = tokens[idx].text;
			cmd.argType = (tokens[idx].type == Token::QUOTED) ? QUOTED : FILENAME;
		}
		return cmd;
	}

	if (idx < tokens.size() && tokens[idx].type == Token::WORD && !tokens[idx].text.empty() && tokens[idx].text[0] == '-') {
		cmd.option = tokens[idx++].text;
	}

	if (idx < tokens.size() && (tokens[idx].type == Token::WORD || tokens[idx].type == Token::QUOTED)) {
		cmd.argument = tokens[idx].text;
		cmd.argType = tokens[idx++].type == Token::QUOTED ? QUOTED : FILENAME;
	}

	while (idx < tokens.size()) {
		Token::Type tt = tokens[idx].type;

		if (tt == Token::REDIRECT_IN) {
			if (idx + 1 >= tokens.size() || tokens[idx + 1].type != Token::WORD) {
				throw SyntaxError("Expected filename after '<'", tokens[idx].position);
			}
			if (cmd.argType != NONE) {
				throw SemanticError("Cannot redirect input when argument is already specified");
			}
			cmd.inputRedirect = tokens[idx + 1].text;
			idx += 2;
		}
		else if (tt == Token::REDIRECT_OUT || tt == Token::APPEND) {
			if (idx + 1 >= tokens.size() || tokens[idx + 1].type != Token::WORD) {
				throw SyntaxError("Expected filename after '>'", tokens[idx].position);
			}
			cmd.outputRedirect = tokens[idx + 1].text;
			cmd.appendOutput = (tt == Token::APPEND);	
			idx += 2;
		}
		else {
			throw SyntaxError("interpretGroup: Unexpected token", tokens[idx].position);
		}
	}

	return cmd;
}