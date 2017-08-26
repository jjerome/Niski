#include "gtest/gtest.h"
#include "utils/Assert.h"

typedef std::exception AssertThrown;

Niski::Utils::Assert::callBackReturnVal testAssertFunction(const std::string& errorMessage, const std::string& fileName, const std::string& functionName, int32_t line)
{
	throw AssertThrown();
}

TEST(AssertTests, Asserts)
{
	//
	// TODO: Terrible name..

	//
	// Install our callback and store the old one to reinstall after we're done (as to
	// keep everything reliable). 
	auto oldAssertCallBack = Niski::Utils::Assert::getAssertCallBack();
	Niski::Utils::Assert::installAssertCallBack(testAssertFunction);

	EXPECT_THROW({
		Niski::Utils::Assert(false, "should fail", __FILE__,  __FUNCSIG__, __LINE__);
	}, AssertThrown);

	EXPECT_NO_THROW({
		Niski::Utils::Assert(true, "should not fail", __FILE__,  __FUNCSIG__, __LINE__);
	});

	//
	// Install the old callback again.
	Niski::Utils::Assert::installAssertCallBack(oldAssertCallBack);
}