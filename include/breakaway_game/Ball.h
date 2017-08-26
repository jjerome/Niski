#ifndef __BREAKAWAY_GAME_BALL__
#define  __BREAKAWAY_GAME_BALL__

#include "engine/Entity.h"
#include "breakaway_game/BreakAwayWorld.h"
#include "math/Vec2d.h"

namespace Niski
{
	namespace BreakAway
	{
		class Ball : public Niski::Engine::Entity
		{
		public:
			Ball(World* world, const Niski::Math::Vector2D<float>& initialPosition, 
				const Niski::Math::Vector2D<float>& initialVelocity, float radius);
			~Ball(void);

			void render(Niski::Renderer::Renderer& renderer) const;
			void reset(void);
			void onTouch(Niski::Engine::Entity* ent);

		private:
			Niski::Math::Vector2D<float>	initialPosition_;
			Niski::Math::Vector2D<float>	initialVelocity_;
			float							radius_;
		};
	}
}

#endif