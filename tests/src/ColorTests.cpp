#include "gtest/gtest.h"
#include "utils/Color.h"

TEST(ColorTests, Initialization)
{
	//
	// Yawn...
	Niski::Utils::Color blue(0, 0, 255, 255);

	EXPECT_TRUE(blue.r == 0);
	EXPECT_TRUE(blue.g == 0);
	EXPECT_TRUE(blue.b == 255);
	EXPECT_TRUE(blue.a == 255);

	Niski::Utils::Color white(Niski::Utils::Color::white);

	EXPECT_TRUE(white.r == 255);
	EXPECT_TRUE(white.g == 255);
	EXPECT_TRUE(white.b == 255);
	EXPECT_TRUE(white.a == 255);
}