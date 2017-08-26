#ifndef __MATH_MATH_H__
#define __MATH_MATH_H__

#include <cstdint>
#include <cmath>

//
// General math functions / constants

namespace Niski
{
	namespace Math
	{
		const double pi = 3.14159265358979323846;

		//
		// Slower method than bit twiddling but is
		// portable to x64. We'll see. 
		inline uint32_t roundUpToPowerOfTwo(uint32_t x)
		{
			//
			// TODO: Change from 1 to some preprocessor definition
			// - only enable the bit twiddling on 32bit arch
#if 1
			return static_cast<uint32_t>(pow(2, ceil(log(x) / log(2))));
#else
			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			x++;
			
			return x;
#endif
		}

		template<class T>
		inline void clamp(T& val, const T& min, const T& max)
		{
			if(val < min)
			{
				val = min;
			}

			if(val > max)
			{
				val = max;
			}
		}
	}
}

#endif