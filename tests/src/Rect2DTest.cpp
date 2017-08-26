#include "gtest/gtest.h"
#include "math/Rectangle.h"

TEST(Rect2DTests, Initialization)
{
	Niski::Math::Rect2D firstRect(0, 0, 20, 20);

	EXPECT_EQ(firstRect.top, 0);
	EXPECT_EQ(firstRect.bottom, 20);

	EXPECT_EQ(firstRect.left, 0);
	EXPECT_EQ(firstRect.right, 20);
}

TEST(Rect2DTests, Equal)
{
	Niski::Math::Rect2D firstRect(0, 0, 20, 20);

	{
		Niski::Math::Rect2D secondRect(0, 0, 20, 20);
		EXPECT_TRUE(firstRect.equal(secondRect));
	}

	{
		Niski::Math::Rect2D secondRect(0, 1, 20, 20);
		EXPECT_FALSE(firstRect.equal(secondRect));
	}
}

TEST(Rect2DTests, PointInRect)
{
	Niski::Math::Rect2D firstRect(0, 0, 20, 20);
	
	EXPECT_TRUE(firstRect.isPointInRect(Niski::Math::Vector2D<int32_t>(5, 5)));

	//
	// Y is outside of the rectangle.
	EXPECT_FALSE(firstRect.isPointInRect(Niski::Math::Vector2D<int32_t>(5, 25)));

	//
	// X is outside of the rectangle.
	EXPECT_FALSE(firstRect.isPointInRect(Niski::Math::Vector2D<int32_t>(25, 5)));
}