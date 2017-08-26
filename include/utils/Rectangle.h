#ifndef __UTILS_RECTANGLE_H__
#define __UTILS_RECTANGLE_H__

#include <windows.h>

namespace Niski
{
	namespace Utils
	{
		class Rect2D
		{

		public:
			Rect2D(int inTop, int inLeft, int inBottom, int inRight);
			Rect2D(const Rect2D& rect);
			Rect2D(RECT rect);

			~Rect2D(void);

			RECT toWin32Rect(void);

			int top;
			int left;
			int bottom;
			int right;
		};
	}
}


#endif