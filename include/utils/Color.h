#ifndef __UTILS_COLOR_H__
#define __UTILS_COLOR_H__

#include <cstdint>

namespace Niski
{
	namespace Utils
	{
		class Color
		{
		public:
			enum Colors
			{
				white = 0,
				black,
				blue,
				red,
				green
			};

		public:
			Color(void) : r(0), g(0), b(0), a(0) {}
			Color(int32_t inR, int32_t inG, int32_t inB, int32_t inA);
			Color(Colors color);

			~Color(void);

			void clamp(void);

			int32_t r;
			int32_t g;
			int32_t b;
			int32_t a;
		};
	}
}

#endif