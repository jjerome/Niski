#ifndef __CONSOLE_COMMANDS_H__
#define __CONSOLE_COMMANDS_H__

#include "engine/ConCommand.h"
#include "utils/Log.h"
#include <sstream>
#include <iostream>
#include <mutex>

class shouldQuit
{
public:
	shouldQuit(void) : shouldQuit_(false)
	{}

	~shouldQuit()
	{}

	bool getShouldQuit(void) const { return shouldQuit_; }
	void setShouldQuit(bool val) { m_.lock(); shouldQuit_ = true; m_.unlock(); }

private:
	std::mutex m_;
	bool shouldQuit_;
};

class QuitCmd : public Niski::Engine::ConCommand
{
public:
	QuitCmd(shouldQuit* quit) : quit_(quit), Niski::Engine::ConCommand("Engine::Quit")
	{}

	~QuitCmd(void)
	{}

	void run(const std::vector<std::string>& args)
	{
		quit_->setShouldQuit(true);
	}

private:
	shouldQuit* quit_;
};

class TestCmd : public Niski::Engine::ConCommand
{
public:
	TestCmd(void) : Niski::Engine::ConCommand("Engine::Test")
	{}

	~TestCmd(void)
	{}

	void run(const std::vector<std::string>& args)
	{
		Niski::Utils::information("Engine::Test has run!");
	}
};

class EchoCmd : public Niski::Engine::ConCommand
{
public:
	EchoCmd(void) : Niski::Engine::ConCommand("Engine::Echo")
	{}

	void run(const std::vector<std::string>& args)
	{
		std::ostringstream oss;
		oss << "Echo ran with arguments: \n";

		for (std::string arg : args)
		{
			oss << "\t" << arg << "\n";
		}

		std::cout << oss.str() << std::endl;;
	}
};

#endif