#ifndef __UTILS_ASSERT_H__
#define __UTILS_ASSERT_H__

#include <string>
#include <cstdint>
#include <functional>

namespace Niski
{
	namespace Utils
	{
		class Assert
		{
		public:
			enum callBackReturnVal
			{
				ignore = 0,
				ignoreAll = 1,
				debug = 2,
				quit
			};

			typedef callBackReturnVal(*AssertCallBack)(const std::string&, const std::string&, const std::string&, int32_t); 

		//
		// Static methods..
		public:
			static void installAssertCallBack(AssertCallBack assertCallBack);
			static AssertCallBack getAssertCallBack(void);
			static AssertCallBack assertCallBack_;

		public:
			Assert(bool assertion, const std::string& errorMessage, const std::string& fileName, const std::string& functionName, int32_t line);
			~Assert(void);
		};
	}
}

#endif