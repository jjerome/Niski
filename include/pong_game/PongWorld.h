#ifndef __PONG_GAME_PONGWORLD_H__
#define __PONG_GAME_PONGWORLD_H__

#include "math/Rectangle.h"
#include "engine/World.h"

namespace Niski
{
	namespace Pong_Game
	{
		class PongWorld : public Niski::Engine::World
		{
		public:
			PongWorld(Niski::Math::Rect2D& bounds);
			~PongWorld(void);

			virtual void render(Niski::Renderer::Renderer& renderer) const;
		};
	}
}

#endif