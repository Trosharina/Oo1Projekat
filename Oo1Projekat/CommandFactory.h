#pragma once
#include "Command.h"
#include <functional>
#include <unordered_map>
#include <memory>

using namespace std;

class CommandFactory
{
public:
	CommandFactory();
	unique_ptr<Command> create(const string& commandName) const;
private:
	unordered_map<string, function<unique_ptr<Command>()>> commandFactory;

};

