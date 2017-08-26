#ifndef __BREAKAWAY_GAME_PADDLE__
#define __BREAKAWAY_GAME_PADDLE__
#include "breakaway_game/BreakAwayPlayer.h"
#include "engine/Entity.h"

namespace Niski
{
	namespace BreakAway
	{
		class Player;

		class Paddle : public Niski::Engine::Entity
		{
		public:
			Paddle(Player* owner, const Niski::Math::Vector2D<float>& initialPosition);
			~Paddle(void);

			void think(const double deltaTime);
			void render(Niski::Renderer::Renderer& renderer) const;
			void onTouch(Niski::Engine::Entity* ent);

		private:
			Niski::Math::Vector2D<float>	initialPosition_;
			Niski::Math::Vector2D<float>	positionToApproach_;
			Player*							owner_;
		};
	}
}

#endif