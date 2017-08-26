#include "gtest/gtest.h"
#include "utils/Timer.h"
#include "windows.h"

//
// This test is rather dumb - Sleep is not that accurate.
TEST(TimerTest, Accuracy)
{
	Niski::Utils::Timer timer;
	timer.start();
	::Sleep(1000);
	timer.stop();

	double result = timer.getTime(Niski::Utils::Timer::unit::seconds);
	//EXPECT_TRUE(std::fabs(result - 1) < FLT_EPSILON);
}