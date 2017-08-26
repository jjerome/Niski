#ifndef __UTILS_HELPERS_H__
#define __UTILS_HELPERS_H__

#include <ctime>

namespace Niski
{
	namespace Utils
	{
		//
		// Quick and dirty non-macro function for unreferenced params.
		template<class T>
		inline void UnreferencedParameter(const T& param)
		{
			param;
		}

		//
		// Helper class to quickly get the local time. 
		// Also fixes some of the questionable designs in the timeData struct
		// Check functions for more information on any changes (most now start from 1, rather than 0)
		class LocalTime
		{
		public:
			LocalTime(void)
			{
				refresh();
			}

			~LocalTime(void)
			{
				//
				//
			}

			void refresh(void)
			{
				time_t time;

				::time(&time);

				//
				// Avoid annoying MSVC errors.
#ifdef _MSC_VER
				localtime_s(&timeData_, &time);
#else
				timeData_ = localtime(&time);
#endif
			}

			//
			// Day of the week (1, 7)
			int32_t getWeekDay(void) const
			{
				return timeData_.tm_wday + 1;
			}

			int32_t getMonthDay(void) const
			{
				return timeData_.tm_mday;
			}

			int32_t getYearDay(void) const
			{
				return timeData_.tm_yday;
			}

			//
			// Month of the year (1, 12)
			int32_t getMonth(void) const
			{
				return timeData_.tm_mon + 1;
			}

			//
			// Years since 0 B.C.
			int32_t getYear(void) const
			{
				return timeData_.tm_year + 1900;
			}

			//
			// Hour of the day (1, 24)
			int32_t getHour(void) const
			{
				return timeData_.tm_hour + 1;
			}

			int32_t getMinute(void) const
			{
				return timeData_.tm_min;
			}

			int32_t getSecond(void) const
			{
				return timeData_.tm_sec;
			}

		private:
			struct tm timeData_;
		};
	}
}

#endif