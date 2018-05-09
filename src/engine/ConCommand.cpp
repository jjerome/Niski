#include "engine/ConCommand.h"
#include "utils/Helpers.h"
#include "utils/StringUtils.h"

using namespace Niski::Engine;

//
// Static ConCommand methods

ConCommand::List& ConCommand::getList(void)
{
	static ConCommand::List list;
	return list;
}

ConCommand* ConCommand::getCommand(const std::string& name)
{
	ConCommand::List& list = getList();

	for(auto command : list)
	{
		if(Niski::Utils::String::toLower(command->getName()) == Niski::Utils::String::toLower(name))
		{
			return command;
		}
	}

	return nullptr;
}

void ConCommand::addCommand(ConCommand* cmd)
{
	getList().push_back(cmd);
}

void ConCommand::removeCommand(ConCommand* cmd)
{
	getList().remove(cmd);
}

//
// Non-static methods

ConCommand::ConCommand(const std::string& name) : name_(name)
{
	addCommand(this);
}

ConCommand::~ConCommand(void)
{
	removeCommand(this);
}

const std::string& ConCommand::getName(void) const
{
	return name_;
}

void ConCommand::run(const std::vector<std::string>& args)
{
	//
	//
	Niski::Utils::UnreferencedParameter(args);
}