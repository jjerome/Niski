#ifndef __PONG_GAME_GAMERULES_H__
#define __PONG_GAME_GAMERULES_H__

#include "engine/ConCommand.h"
#include "math/Rectangle.h"
#include "pong_game/PongWorld.h"
#include "pong_game/Ball.h"
#include "pong_game/Paddle.h"

#include <list>

namespace Niski
{
	namespace Pong_Game
	{
		class GameRules;

		class PauseCmd : public Niski::Engine::ConCommand
		{
		public:
			PauseCmd(Niski::Pong_Game::GameRules* gameRules) : Niski::Engine::ConCommand("PongGame::GameRules::Pause"), gameRules_(gameRules)
			{}

			void run(void);

		private:
			Niski::Pong_Game::GameRules* gameRules_;
		};

		class ResetCmd : public Niski::Engine::ConCommand
		{
		public:
			ResetCmd(Niski::Pong_Game::GameRules* gameRules) : Niski::Engine::ConCommand("PongGame::GameRules::Reset"), gameRules_(gameRules)
			{}

			~ResetCmd(void)
			{}

			void run(void);

		private:
			Niski::Pong_Game::GameRules* gameRules_;
		};

		class GameRules
		{
		public:
			GameRules(void);
			~GameRules(void);

			void createGameWorld(Niski::Math::Rect2D& bounds);
			PongPlayer* createPlayer(const std::string& name, float x);
			PongPlayer* createBot(float x);
			Ball*	createBall(/*???*/);

			void onScore(Niski::Math::Vector2D<float>& ballPosition);

			void start(void);
			void think(double deltaTime);
			void render(Niski::Renderer::Renderer& renderer) const;

			void reset(void);
			void pause(void);

			bool isPaused(void) const { return isPaused_; }

		private:
			PongWorld*				world_;
			std::list<PongPlayer*>	players_;
			Ball*					ball_;
			bool					needReset_;
			bool					isPaused_;

			ResetCmd				resetCmd_;
			PauseCmd				pauseCmd_;
		};
	}
}

#endif