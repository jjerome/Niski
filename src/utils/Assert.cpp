#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Utils;

Assert::AssertCallBack Assert::assertCallBack_ = nullptr;

void Assert::installAssertCallBack(AssertCallBack assertCallBack)
{
	assertCallBack_ = assertCallBack;
}

Assert::AssertCallBack Assert::getAssertCallBack(void)
{
	return assertCallBack_;
}

Assert::Assert(bool assertion, const std::string& errorMessage, const std::string& fileName, const std::string& functionName, int32_t line)
{
	if(assertion)
	{
		return;
	}

	AssertCallBack assertCB = getAssertCallBack();

	if(assertCB == nullptr)
	{
		//
		// Log..
		Niski::Utils::error("Assert system has no valid assert callback!");

		return;
	}

	//
	// TODO: Failed asserts should be logged somewhere
	std::ostringstream data("Assert failed\n\n");
	data << "Error: " << errorMessage << "\n\nFile: " << fileName << "\n\nLine: " << line;
	Niski::Utils::error(data.str());

	//
	// Call the callback..
	callBackReturnVal ret = (*assertCB)(errorMessage, fileName, functionName, line);

	switch(ret)
	{
	case ignoreAll:
		//
		// TODO: 
		Niski::Utils::information("User is ignoring all asserts");
		break;

	case ignore:
		Niski::Utils::information("User ignored assert");
		break;

	case debug:
#ifdef _MSC_VER
		__asm
		{
			int 3;
		}
#else
#	error "Debug command not defined for this compiler/platform"
#endif
		Niski::Utils::information("User attempted to debug the assert");
		break;

	case quit:
	default:
		//
		// TODO: The best way to do this?
		Niski::Utils::information("User quit because of the assert");
		exit(0);
		break;
	}
}

Assert::~Assert(void)
{}