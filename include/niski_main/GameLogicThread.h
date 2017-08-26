#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include "niski_main/ConsoleCommands.h"
#include "niski_main/Niski.h"
#include "pong_game/GameRules.h"
#include "utils/Timer.h"
#include "gui/RootPanel.h"

class GameLogicThread
{
public:
	enum status
	{
		paused = 0,
		quitting,
		ok,
	};

public:
	GameLogicThread(int32_t ticksPerSecond, Niski::Pong_Game::GameRules* gameRules, Niski::GUI::RootPanel* rootPanel_, shouldQuit* quit, std::mutex* lock);
	~GameLogicThread(void);

	//
	// Initialize is overriden
	void initialize(void);

	//
	//
	status getStatus(void) const;

	void run(void);
	//
	// Think is overriden. 
	void think(double frameTime);

private:
	int32_t ticksPerSecond_;
	Niski::Pong_Game::GameRules* gameRules_;
	Niski::GUI::RootPanel* rootPanel_;
	std::mutex* lock_;
	shouldQuit* quit_;
	Niski::Utils::Timer timer_;
};

void gameLogicThreadFunc(shouldQuit& quit, Niski::Pong_Game::GameRules& gameRules, Niski::GUI::RootPanel& rootPanel, std::mutex& logicMutex);

#endif