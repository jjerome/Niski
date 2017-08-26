#include "niski_main/GameLogicThread.h"

#include "gui/Label.h"
#include "utils/Timer.h"
#include "utils/Color.h"

/*
===============================================================================

	Note that this function is temporary and is only used for testing
	out code as it is written. Ideally this would all be handled with much 
	more grace than it is currently.

===============================================================================
*/

GameLogicThread::GameLogicThread(int32_t ticksPerSecond, Niski::Pong_Game::GameRules* gameRules, Niski::GUI::RootPanel* rootPanel, shouldQuit* quit, std::mutex* lock) 
	: ticksPerSecond_(ticksPerSecond), gameRules_(gameRules), rootPanel_(rootPanel), quit_(quit), lock_(lock)
{
	initialize();
}

GameLogicThread::~GameLogicThread(void)
{}

void GameLogicThread::initialize(void)
{
	//
	// Initialize the game rules so the game is ready to activate!
	gameRules_->start();
}

GameLogicThread::status GameLogicThread::getStatus(void) const
{
	if(quit_->getShouldQuit())
	{
		return status::quitting;
	}

	if(gameRules_->isPaused())
	{
		return status::paused;
	}

	return status::ok;
}

void GameLogicThread::run(void)
{
	const double secondsPerTick = 1.0 / ticksPerSecond_;
	//
	// Accumulates frame time, so excess time isn't just disposed of. 
	double accumulator = 0.0;

	//
	// TODO: Pausing no longer works!
	while(getStatus() != status::quitting)
	{
		//
		// Stop the timer now so we can calculate how long the last frame took.
		timer_.stop();

		//
		// Gets the amount of time (in seconds) the timer took to get to this
		// spot.
		double frameTime = timer_.getTime(Niski::Utils::Timer::seconds);

		/*printf("[Game Logic] Frame time: %f\n", frameTime);*/

		//
		// Clamp frametime
		Niski::Math::clamp(frameTime, frameTime, 0.25);

		accumulator += frameTime;

		//
		// Reset the timer to start timing how long the next frame will take.
		timer_.reset();

		//
		// Check if we are allowed to render.
		if(accumulator >= secondsPerTick)
		{
			//
			// Let us catch up if we are behind.
			do
			{
				lock_->lock();
				{
					think(secondsPerTick);
				}
				lock_->unlock();
				accumulator -= secondsPerTick;
			} while(accumulator >= secondsPerTick);
		}
		else
		{
			DWORD sleepTime = DWORD(secondsPerTick * 1000);

			if(sleepTime > 0)
			{
				::Sleep(sleepTime);
			}
		}
	}
}

void GameLogicThread::think(double frameTime)
{
	gameRules_->think(frameTime);
}

void gameLogicThreadFunc(shouldQuit& quit, Niski::Pong_Game::GameRules& gameRules, Niski::GUI::RootPanel& rootPanel, std::mutex& logicMutex)
{
	GameLogicThread glogic(60, &gameRules, &rootPanel, &quit, &logicMutex);	
	glogic.run();
}