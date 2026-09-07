#include "Interpreter.h"
#include <iostream>
#include "InterpreterError.h"
#include "LexicalError.h"
#include "CommandError.h"
#include "SemanticError.h"
#include "StringInput.h"
#include "FileInput.h"
#include "ConsoleInput.h"
#include "FileOutput.h"
#include "ConsoleOutput.h"
#include "StringOutput.h"

void Interpreter::run() {
	while (true) {
		cout << prompt;

		string line;
		if (!getline(cin, line))
			break;
		
		executeLineSafely(line);
	}
}

void Interpreter::executeLineSafely(const string& line) {
	try {
		executeLine(line);
	}
	catch (const LexicalError& e) {
		cerr << e.format() << endl;
	}
	catch (const InterpreterError& e) {
		cerr << "Error: " << e.what() << endl;
	}

	if (cin.eof())
		cin.clear();
}

void Interpreter::executeLine(const string& line) {
	CommandLine cmdLine = parser.parse(line);

	if (cmdLine.commands.empty())
		return;

	if (cmdLine.commands.size() == 1) {
		executeSingle(cmdLine.commands[0]);
	}
	else {
		executePipe(cmdLine.commands);
	}
	cout << endl;
}

unique_ptr<InputStream> Interpreter::makeInput(const ParsedCommand& pc, const Command& command) const {
	if (!command.needsInput())
		return make_unique<StringInput>("");

	if (!pc.inputRedirect.empty()) {
		return make_unique<FileInput>(pc.inputRedirect);
	}

	switch (pc.argType) {
	case QUOTED:
		return make_unique<StringInput>(pc.argument);
	case FILENAME:
		return make_unique<FileInput>(pc.argument);
	case NONE:
	default:
		return make_unique<ConsoleInput>();
	}
}

unique_ptr<OutputStream> Interpreter::makeOutput(const ParsedCommand& pc) const {
	if (!pc.outputRedirect.empty()) {
		return make_unique<FileOutput>(pc.outputRedirect, pc.appendOutput);
	}
	return make_unique<ConsoleOutput>();
}

void Interpreter::executeSingle(const ParsedCommand& pc) {
	unique_ptr<Command> command = commandFactory.create(pc.name);
	if (!command) {
		throw CommandError("Unknown command: " + pc.name);
	}

	command->setOption(pc.option);
	command->setArgument(pc.argument);
	command->setRawTokens(pc.rawTokens);

	unique_ptr<InputStream> input = makeInput(pc, *command);
	unique_ptr<OutputStream> output = makeOutput(pc);

	command->execute(*input, *output, *this);
}

void Interpreter::executePipe(const vector<ParsedCommand>& pc) {
	validatePipe(pc);

	string pipeBuffer;

	for (size_t i = 0; i < pc.size(); i++) {
		const ParsedCommand& cmd = pc[i];
		bool isFirst = (i == 0);
		bool isLast = (i == pc.size() - 1);

		unique_ptr<Command> command = commandFactory.create(cmd.name);
		if (!command) {
			throw CommandError("Unknown command: " + cmd.name);
		}

		command->setOption(cmd.option);
		command->setArgument(cmd.argument);
		command->setRawTokens(cmd.rawTokens);

		unique_ptr<InputStream> in;
		if (isFirst) {
			in = makeInput(cmd, *command);
		}
		else {
			in = make_unique<StringInput>(pipeBuffer);
		}

		unique_ptr<OutputStream> out;
		unique_ptr<StringOutput> capture;
		if (isLast) {
			out = makeOutput(cmd);
		}
		else {
			capture = make_unique<StringOutput>();
		}

		command->execute(*in, isLast ? *out : *capture, *this);

		if (!isLast)
			pipeBuffer = capture->getBuffer();
	}
}

void Interpreter::validatePipe(const vector<ParsedCommand>& pcs) const {
	for (size_t i = 0; i < pcs.size(); i++) {
		const ParsedCommand& pc = pcs[i];
		bool isFirst = (i == 0);
		bool isLast = (i == pcs.size() - 1);

		unique_ptr<Command> probe = commandFactory.create(pc.name);
		if (!probe)
			throw CommandError("Unknown command: " + pc.name);

		if (!isFirst && !probe->needsInput())
			throw SemanticError(pc.name + ": command without input must not be in the middle of a pipeline");

		if (!isFirst && pc.argType != NONE)
			throw SemanticError(pc.name + ": argument already provided by previous command in the pipeline");
		if (!isFirst && !pc.inputRedirect.empty())
			throw SemanticError(pc.name + ": cannot redirect input in the middle of a pipeline");
		if (!isLast && !pc.outputRedirect.empty())
			throw SemanticError(pc.name + ": cannot redirect output in the middle of a pipeline");
	}
}

void Interpreter::setPrompt(const string& newPrompt) {
	prompt = newPrompt;
}