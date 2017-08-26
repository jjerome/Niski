#ifndef __BREAKAWAY_GAME_WORLD__
#define __BREAKAWAY_GAME_WORLD__

#include "engine/World.h"
#include "renderer/Renderer.h"
#include "utils/Color.h"

namespace Niski
{
	namespace BreakAway
	{
		class World : public Niski::Engine::World
		{
		public:
			World(const Niski::Math::Rect2D& bounds, const Niski::Utils::Color& backgroundColor);
			~World(void);

			void render(Niski::Renderer::Renderer& renderer) const;

		private:
			Niski::Utils::Color backgroundColor_;
		};
	}
}

#endif