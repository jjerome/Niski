#ifndef __MATH_RECTANGLE_H__
#define __MATH_RECTANGLE_H__

#include "math/Vec2d.h"
#include <cstdint>

#include "utils/win32/Win32Includes.h"

namespace Niski
{
	namespace Math
	{
		class Rect2D
		{
		public:

			Rect2D(int32_t inTop, int32_t inLeft, int32_t inBottom, int32_t inRight) : top(inTop), left(inLeft), bottom(inBottom), right(inRight) {}
			Rect2D(const Rect2D& rect) : top(rect.top), left(rect.left), bottom(rect.bottom), right(rect.right) {}
			Rect2D(RECT rect) : top(rect.top), left(rect.left), bottom(rect.bottom), right(rect.right) {}
			Rect2D(void) : top(0), left(0), bottom(0), right(0) {}

			~Rect2D(void) {}

			inline bool		operator ==(const Rect2D& rect)							const;
			inline bool		operator !=(const Rect2D& rect)							const;

			inline Rect2D	operator +(const Rect2D& rect)							const;

			inline bool		equal(const Rect2D& rect)								const;
			//
			// toWin32Rect needs to be moved to utils/win32 somewhere.
			inline RECT		toWin32Rect(void)										const;
			template<class T>
			inline bool		isPointInRect(const Niski::Math::Vector2D<T>& point)	const;

		public:
			int32_t top;
			int32_t left;
			int32_t bottom;
			int32_t right;
		};

		inline bool Rect2D::operator ==(const Rect2D& rect) const 
		{
			return equal(rect);
		}

		inline bool Rect2D::operator !=(const Rect2D& rect) const 
		{
			return !equal(rect);
		}

		inline Rect2D Rect2D::operator+(const Rect2D& rect) const
		{
			return Rect2D(top + rect.top, left + rect.left, bottom + rect.bottom, right + rect.right);
		}

		inline bool Rect2D::equal(const Rect2D& rect) const
		{
			//
			// Don't bother combining everything here into one mega if statement. This is far more readable.
			if(top != rect.top)
			{
				return false;
			}

			if(bottom != rect.bottom)
			{
				return false;
			}

			if(left != rect.left)
			{
				return false;
			}

			if(right != rect.right)
			{
				return false;
			}

			return true;
		}

		inline RECT Rect2D::toWin32Rect(void) const
		{
			RECT rect;
			rect.top = top;
			rect.left = left;
			rect.bottom = bottom;
			rect.right = right;

			return rect;
		}

		template<class T>
		inline bool Rect2D::isPointInRect(const Niski::Math::Vector2D<T>& point) const
		{
			if((point.x > left && point.x < (left + right)) && (point.y > top && point.y < (top + bottom)))
			{
				return true;
			}

			return false;
		}
	}
}

#endif