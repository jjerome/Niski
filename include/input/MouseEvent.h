#ifndef __INPUT_MOUSEEVENT_H__
#define __INPUT_MOUSEEVENT_H__

#include "math/Vec2d.h"
#include <cstdint>

namespace Niski
{
	namespace Input
	{
		class MouseEvent
		{
		public:
			MouseEvent(const Niski::Math::Vector2D<int32_t>& difference) : difference_(difference) {}
			~MouseEvent(void) {}

			const Niski::Math::Vector2D<int32_t>& getPositionDifference(void) const
			{
				return difference_;
			}

		private:
			Niski::Math::Vector2D<int32_t> difference_;
		};
	}
}

#endif