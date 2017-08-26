#ifndef __UTILS_TIMER_H__
#define __UTILS_TIMER_H__

#include <cstdint>
#include <stdexcept>
#include "win32/Win32Includes.h"

//
// High resolution timer.. (since MSVC doesn't provide the standard's with the accuracy we need..)
namespace Niski
{
	namespace Utils
	{
		class Timer
		{
		public:
			enum unit
			{
				microseconds,
				milliseconds,
				seconds
			};

		public:
			Timer(void);
			~Timer(void);

			void start(void);
			void reset(void);
			void stop(void);

			double getTime(unit unitType = unit::seconds);

		private:
			int64_t frequency_;
			int64_t startTime_;
			int64_t stopTime_;
		};

		//
		// Exceptions.
		class TimerFailedToInitialize : public std::runtime_error
		{
		public:
			TimerFailedToInitialize(const std::string& message) : runtime_error(message)
			{}
		};

		class TimerFailedToQueryTime : public std::runtime_error
		{
		public:
			TimerFailedToQueryTime(const std::string& message) : runtime_error(message)
			{}
		};
	}
}

#endif