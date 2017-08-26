#ifndef __BREAKAWAY_GAME_BRICK__
#define __BREAKAWAY_GAME_BRICK__

#include "breakaway_game/BreakAwayWorld.h"
#include "engine/Entity.h"
#include "utils/Color.h"

namespace Niski
{
	namespace BreakAway
	{
		class Brick : public Niski::Engine::Entity
		{
		public:
			Brick(World* world, const std::string& brickName, const Niski::Math::Vector2D<float>& position, const Niski::Utils::Color& color, int16_t health = 0);
			~Brick(void);

			void onTouch(Niski::Engine::Entity* ent);

		private:
			int16_t health_;
			Niski::Utils::Color color_;
		};
	}
}

#endif