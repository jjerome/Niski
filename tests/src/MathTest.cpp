#include "gtest/gtest.h"
#include "math/Math.h"

TEST(MathTests, roundUpToPowerOfTwo)
{
	//
	// 3 should be rounded up to 2^2
	EXPECT_EQ(Niski::Math::roundUpToPowerOfTwo(3), 4);

	//
	// 40 should be rounded up to 2^6
	EXPECT_EQ(Niski::Math::roundUpToPowerOfTwo(40), 64);

	//
	// 4000 should be rounded up to 2^12
	EXPECT_EQ(Niski::Math::roundUpToPowerOfTwo(4000), 4096);
}

TEST(MathTests, clamp)
{
	//
	// This value shouldn't be clamped (it is within the bounds)
	{
		int32_t val = 5;
		Niski::Math::clamp(val, 1, 20);

		EXPECT_EQ(val, 5);
	}

	//
	// This value should be clamped to min
	{
		int32_t val = 0;
		Niski::Math::clamp(val, 1, 20);

		EXPECT_EQ(val, 1);
	}

	//
	// This value should be clamped to max
	{
		int32_t val = 21;
		Niski::Math::clamp(val, 1, 20);

		EXPECT_EQ(val, 20);
	}
}