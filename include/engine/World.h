#ifndef __ENGINE_WORLD_H__
#define __ENGINE_WORLD_H__

#include "engine/Entity.h"
#include "math/Rectangle.h"

namespace Niski
{
	namespace Engine
	{
		class World : public Entity
		{
		public:
			World(Niski::Math::Rect2D& bounds);
			~World(void);

			void					setBounds(Niski::Math::Rect2D& bounds);
			Niski::Math::Rect2D		getBounds(void) const;

			virtual void			render(Niski::Renderer::Renderer& renderer) const;

		private:
			Niski::Math::Rect2D bounds_;
		};
	}
}

#endif