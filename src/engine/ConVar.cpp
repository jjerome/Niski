#include "engine/ConVar.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include <sstream>

using namespace Niski::Engine;

//
// Static ConVar methods

ConVar::List& ConVar::getConVars(void)
{
	static List list;
	return list;
}

ConVar* ConVar::getConVar(const std::string& name)
{
	ConVar::List list = getConVars();

	for(auto conVar : list)
	{
		if(Niski::Utils::String::toLower(conVar->getName()) == Niski::Utils::String::toLower(name))
		{
			return conVar;
		}
	}

	return nullptr;
}

void ConVar::addConVar(ConVar* var)
{
	if(getConVar(var->getName()) == nullptr)
	{
		getConVars().push_back(var);
	}
	else
	{
		Niski::Utils::bitch("Attempted to add a convar, despite it already being in our list");
	}
}

void ConVar::removeConVar(const std::string& name)
{
	ConVar::List& list = getConVars();

	for(auto it = list.begin(); it != list.end(); ++it)
	{
		if(Niski::Utils::String::toLower((*it)->getName()) == Niski::Utils::String::toLower(name))
		{
			list.erase(it);

			return;
		}
	}
}

void ConVar::removeConVar(ConVar* var)
{
	getConVars().remove(var);
}

//
// Non-static methods

ConVar::ConVar(const std::string& name, const std::string& value, const std::string& helpText /* = "" */, ConVar::callBackFn callBack /* = nullptr */) 
	: name_(name), strValue_(value), helpText_(helpText), callBack_(callBack)
{
	addConVar(this);
}

ConVar::ConVar(const std::string& name, int value, const std::string& helpText /* = "" */, ConVar::callBackFn callBack /* = nullptr */) 
	: name_(name), intValue_(value), helpText_(helpText), callBack_(callBack)
{
	addConVar(this);
}

ConVar::ConVar(const std::string& name, float value, const std::string& helpText /* = "" */, ConVar::callBackFn callBack /* = nullptr */) 
	: name_(name), floatValue_(value), helpText_(helpText), callBack_(callBack)
{
	addConVar(this);
}

ConVar::~ConVar(void)
{
	removeConVar(this);
}

const std::string& ConVar::getName(void) const
{
	return name_;
}

void ConVar::setStrValue(const std::string& value)
{
	std::string oldValue = strValue_;

	strValue_ = value;

	if(callBack_ != nullptr)
	{
		callBack_(this, oldValue, value);
	}
}

const std::string& ConVar::getStrValue(void) const
{
	return strValue_;
}

void ConVar::setIntValue(int value)
{
	std::ostringstream oldValue; oldValue << intValue_;

	intValue_ = value;

	std::ostringstream newValue; newValue << intValue_;

	if(callBack_ != nullptr)
	{
		callBack_(this, oldValue.str(), newValue.str());
	}
}

const int ConVar::getIntValue(void) const
{
	return intValue_;
}

void ConVar::setFloatValue(float value)
{
	std::ostringstream oldValue; oldValue << floatValue_;

	floatValue_ = value;

	std::ostringstream newValue; newValue << floatValue_;

	if(callBack_ != nullptr)
	{
		callBack_(this, oldValue.str(), newValue.str());
	}
}

const float ConVar::getFloatValue(void) const
{
	return floatValue_;
}

void ConVar::setHelpText(const std::string& helpText)
{
	helpText_ = helpText;
}

const std::string& ConVar::getHelpText(void) const
{
	return helpText_;
}