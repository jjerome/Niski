#ifndef __UTILS_STRINGUTILS_H__
#define __UTILS_STRINGUTILS_H__

#include <string>
#include <vector>

namespace Niski
{
	namespace Utils
	{
		namespace String
		{
			//
			// Unicode
			std::wstring toLower(const std::wstring& str);
			std::wstring toUpper(const std::wstring& str);
			std::wstring toWide(const std::string& str);

			//
			// ASCII 
			std::string toLower(const std::string& str);
			std::string toUpper(const std::string& str);

			void parse(const std::string& str, std::vector<std::string>& result);
		}
	}
}

#endif