#include "utils/Timer.h"
#include <sstream>

using namespace Niski::Utils;

Timer::Timer(void)
{
	LARGE_INTEGER largeInt;
	BOOL result = ::QueryPerformanceFrequency(&largeInt);

	if(result == FALSE)
	{
		std::ostringstream err("Failed to query performance frequency.\nWindows API returned: ");
		err << ::GetLastError();

		throw TimerFailedToInitialize(err.str());
	}

	//
	// Record the frequency in microseconds..
	frequency_ = largeInt.QuadPart;
}

Timer::~Timer(void)
{}

void Timer::start(void)
{
	DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

	LARGE_INTEGER largeInt;
	BOOL result = ::QueryPerformanceCounter(&largeInt);

	if(result == FALSE)
	{
		std::ostringstream err("Failed to query performance counter for the start time.\nWindows API returned: ");
		err << ::GetLastError();

		throw TimerFailedToQueryTime(err.str());
	}

	startTime_ = largeInt.QuadPart;

	//
	// Reset stop time.
	stopTime_ = 0;

	::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
}

void Timer::reset(void)
{
	startTime_ = stopTime_ = 0;
	start();
}

void Timer::stop(void)
{
	DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);

	LARGE_INTEGER largeInt;
	BOOL result = ::QueryPerformanceCounter(&largeInt);

	if(result == FALSE)
	{
		std::ostringstream err("Failed to query performance counter for the end time.\nWindows API returned: ");
		err << ::GetLastError();

		throw TimerFailedToQueryTime(err.str());
	}

	stopTime_ = largeInt.QuadPart;

	::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
}

double Timer::getTime(unit unitType)
{
	double modifier;

	switch(unitType)
	{
	case microseconds:
		modifier = 1000000.0;
		break;

	case milliseconds:
		modifier = 1000.0;
		break;

	case seconds:
	default:
		modifier = 1.0;
		break;
	}

	return ((stopTime_ - startTime_) * modifier) / frequency_;
}