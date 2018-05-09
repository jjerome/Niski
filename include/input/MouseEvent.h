#ifndef __INPUT_MOUSEEVENT_H__
#define __INPUT_MOUSEEVENT_H__

#include "math/Vec2d.h"
#include "input/KeyCodes.h"
#include <cstdint>

namespace Niski
{
	namespace Input
	{
		class MouseEvent
		{
		public:
			MouseEvent(const Niski::Math::Vector2D<int32_t>& difference, int32_t wheelScroll) : difference_(difference), wheelScroll_(wheelScroll) {}
			~MouseEvent(void) {}

			const Niski::Math::Vector2D<int32_t>& getPosition(void) const
			{
				return difference_;
			}

		private:
			Niski::Math::Vector2D<int32_t> difference_;
			int32_t						wheelScroll_;
		};
	}
}

#endif