#ifndef __CONSOLE_COMMANDS_H__
#define __CONSOLE_COMMANDS_H__

#include "engine/ConCommand.h"
#include "utils/Log.h"
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

	void run(void)
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

	void run(void)
	{
		Niski::Utils::information("Engine::Test has run!");
		std::cout << "Engine::Test has run!" << std::endl;
	}
};

#endif