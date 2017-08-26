#ifndef __MATH_RANDOM_H__
#define __MATH_RANDOM_H__

#include <cstdlib>
#include <ctime>

namespace Niski
{
	namespace Math
	{
		class Random
		{
		public:
			Random(void) : seed(0)
			{
				setSeed(generateSeed());
			}

			~Random(void)
			{}

			//
			// Generate a random number between min and max
			inline uint32_t randomNumber(uint32_t min, uint32_t max)
			{
				return (::rand() + min) % max;
			}

			//
			// Generates a random seed from the current time. 
			inline uint32_t generateSeed(void)
			{
				return static_cast<uint32_t>(::time(nullptr));
			}

			//
			// Sets the current seed and seeds the random number generator
			inline void setSeed(uint32_t aSeed)
			{
				seed = aSeed;

				::srand(aSeed);
			}

		public:
			uint32_t seed;
		};
	}
}

#endif