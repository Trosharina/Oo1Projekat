#include "CommandFactory.h"
#include "Echo.h"
#include "Time.h"
#include "Date.h"
#include "Touch.h"
#include "Wc.h"
#include "Truncate.h"
#include "Rm.h"
#include "Prompt.h"
#include "Head.h"
#include "Tr.h"
#include "Batch.h"

CommandFactory::CommandFactory() {
	commandFactory["echo"] = []() { return make_unique<Echo>(); };
	commandFactory["time"] = []() { return make_unique<Time>(); };
	commandFactory["date"] = []() { return make_unique<Date>(); };
	commandFactory["touch"] = []() { return make_unique<Touch>(); };
	commandFactory["wc"] = []() { return make_unique<Wc>(); };
	commandFactory["truncate"] = []() { return make_unique<Truncate>(); };
	commandFactory["rm"] = []() { return make_unique<Rm>(); };
	commandFactory["prompt"] = []() { return make_unique<Prompt>(); };
	commandFactory["head"] = []() { return make_unique<Head>(); };
	commandFactory["tr"] = []() { return make_unique<Tr>(); };
	commandFactory["batch"] = []() { return make_unique<Batch>(); };
}

unique_ptr<Command> CommandFactory::create(const string& commandName) const {
	auto it = commandFactory.find(commandName);
	if (it != commandFactory.end())
		return it->second();
	return nullptr;
}