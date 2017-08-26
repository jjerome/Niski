#include "gtest/gtest.h"
#include "utils/StringUtils.h"

TEST(StringTests, toLower)
{
	std::wstring wStr = L"Acquire Hoes";
	std::wstring wStrExpected = L"acquire hoes";

	EXPECT_TRUE(wStrExpected == Niski::Utils::String::toLower(wStr));
	EXPECT_FALSE(wStr == Niski::Utils::String::toLower(wStr));

	std::string bStr = "Acquire Hoes";
	std::string bStrExpected = "acquire hoes";

	EXPECT_TRUE(bStrExpected == Niski::Utils::String::toLower(bStr));
}

TEST(StringTests, toUpper)
{
	std::wstring wStr = L"Acquire Hoes";
	std::wstring wStrExpected = L"ACQUIRE HOES";

	EXPECT_TRUE(wStrExpected == Niski::Utils::String::toUpper(wStr));
	EXPECT_FALSE(wStr == Niski::Utils::String::toUpper(wStr));

	std::string bStr = "Acquire Hoes";
	std::string bStrExpected = "ACQUIRE HOES";

	EXPECT_TRUE(bStrExpected == Niski::Utils::String::toUpper(bStr));
}

TEST(StringTests, parse)
{
	{
		//
		// hello world "this is a quoted string"
		std::string args = "hello world \"this is a quoted string\"";
		std::vector<std::string> result;

		//
		// annoying..
		std::vector<std::string> expectedResult;
		expectedResult.push_back("hello");
		expectedResult.push_back("world");
		expectedResult.push_back("this is a quoted string");

		EXPECT_NO_THROW(Niski::Utils::String::parse(args, result));
		EXPECT_TRUE(result == expectedResult);
	}

	{
		//
		// hello world "this is a \"quoted\" string"
		std::string args = "hello world \"this is a \\\"quoted\\\" string\"";
		std::vector<std::string> result;

		//
		// annoying..
		std::vector<std::string> expectedResult;
		expectedResult.push_back("hello");
		expectedResult.push_back("world");
		expectedResult.push_back("this is a \\\"quoted\\\" string");

		EXPECT_NO_THROW(Niski::Utils::String::parse(args, result));
		EXPECT_TRUE(result == expectedResult);
	}

}