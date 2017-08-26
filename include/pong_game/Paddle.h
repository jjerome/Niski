#ifndef __PONG_GAME_PADDLE_H__
#define __PONG_GAME_PADDLE_H__

#include "engine/Entity.h"
#include "pong_game/PongPlayer.h"
#include "math/Vec2d.h"

namespace Niski
{
	namespace Pong_Game
	{
		//
		// To prevent circular header dependency... 
		class PongPlayer;

		class Paddle : public Niski::Engine::Entity
		{
		public:
			Paddle(PongPlayer* owner, const Niski::Math::Vector2D<float>& initialPosition);
			~Paddle(void);

			void think(const double deltaTime);
			void render(Niski::Renderer::Renderer& renderer) const;
			void reset(void);

			void setApproachVector(const Niski::Math::Vector2D<float>& positionToApproach);

			Niski::Math::Rect2D getBounds(void) const;
			Niski::Math::Rect2D getRenderBounds(void) const;

		private:
			Niski::Math::Vector2D<float>	initialPosition_;
			Niski::Math::Vector2D<float>	positionToApproach_;
			PongPlayer*						owner_;
		};
	}
}

#endif