#ifndef __PONG_GAME_BALL_H__
#define __PONG_GAME_BALL_H__

#include "engine/Entity.h"
#include "pong_game/PongWorld.h"
#include "math/Vec2d.h"

namespace Niski
{
	namespace Pong_Game
	{
		class Ball : public Niski::Engine::Entity
		{
		public:
			Ball(PongWorld* world, const Niski::Math::Vector2D<float>& initialPosition, float radius);
			~Ball(void);

			void render(Niski::Renderer::Renderer& renderer) const;

			void reset(void);

			void onTouch(Entity* ent);

		private:
			Niski::Math::Vector2D<float>	initialPosition_;
			float							radius_;
		};
	}
}

#endif