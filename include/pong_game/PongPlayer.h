#ifndef __PONG_GAME_PONGPLAYER_H__
#define __PONG_GAME_PONGPLAYER_H__

#include <string>

#include "engine/Player.h"
#include "pong_game/PongWorld.h"
#include "pong_game/Paddle.h"

namespace Niski
{
	namespace Pong_Game
	{
		class Paddle;

		class PongPlayer : public Niski::Engine::Player
		{
		public:
			PongPlayer(PongWorld* parent, const Niski::Math::Vector2D<float>& initialPaddlePosition, const std::string& name, bool isBot = false);
			~PongPlayer(void);

			virtual void	think(const double deltaTime);

			void			reset(void);

			void			setScore(int16_t score);
			int16_t			getScore(void) const;

			bool			isHuman(void) const { return !isBot_; }
			bool			isBot(void) const { return isBot_; }

			Paddle*			getPaddle(void) { return paddle_; }

		private:
			Paddle* paddle_;
			bool	isBot_;
			int16_t	score_;
		};
	}
}

#endif