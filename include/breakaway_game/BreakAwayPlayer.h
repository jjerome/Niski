#ifndef __BREAKAWAY_GAME_PLAYER__
#define __BREAKAWAY_GAME_PLAYER__

#include "breakaway_game/BreakAwayWorld.h"
#include "engine/Player.h"

namespace Niski
{
	namespace BreakAway
	{
		class Player : public Niski::Engine::Player
		{
		public:
			Player(World* world, const Niski::Math::Vector2D<float>& initialPosition, bool isBot);
			~Player(void);

			void reset(void);
			void setScore(void);
			int16_t getScore(void) const;
			void think(const double deltaTime);

		private:
			Niski::Math::Vector2D<float> initialPosition_;
			bool isBot_;
			int16_t score_;
		};
	}
}

#endif