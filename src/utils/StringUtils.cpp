#include <sstream>
#include <locale>
#include <vector>
#include "utils/StringUtils.h"

using namespace Niski::Utils;

//
// Unicode
std::wstring String::toLower(const std::wstring& str)
{
	std::wstring destination;
	std::locale loc;

	for(auto ch : str)
	{
		destination += std::tolower(ch, loc);
	}

	return destination;
}

std::wstring String::toUpper(const std::wstring& str)
{
	std::wstring destination;
	std::locale loc;

	for(auto ch : str)
	{
		destination += std::toupper(ch, loc);
	}

	return destination;
}

// TODO: Use widen() ? 

std::wstring String::toWide(const std::string& str)
{
	std::wostringstream dest;

	dest << str.c_str();

	return dest.str();
}

//
// ASCII 
std::string String::toLower(const std::string& str)
{
	std::string destination;
	std::locale loc;

	for(auto ch : str)
	{
		destination += std::tolower(ch, loc);
	}

	return destination;
}

std::string String::toUpper(const std::string& str)
{
	std::string destination;
	std::locale loc;

	for(auto ch : str)
	{
		destination += std::toupper(ch, loc);
	}

	return destination;
}

void String::parse(const std::string& str, std::vector<std::string>& result)
{
	//
	// Adapted with small changes from http://www.gamedev.net/topic/320087-c-string-parsing-with-stringstream/?view=findpost&p=3058954
	std::stringstream ss(str);
	std::string item;

	while(ss >> item)
	{
		if(item[0] == '"')
		{
			auto lastCharacterPos = item.length() - 1;

			//
			// If we cannot find the end quote in this item.
			if(item[lastCharacterPos] != '"')
			{
				std::string restOfItem;
				bool found = false;

				//
				// Do a search for the end of quote. Make sure it isn't
				// nullified by "\"
				do 
				{
					getline(ss, restOfItem, '"');			

					//
					// Subtract one to get the previous character
					auto ch = restOfItem[restOfItem.length() - 1];
					if (ch != '\\' || ss.eof())
					{
						found = true;
					}
					else
					{
						item += restOfItem;
						item += '"';
					}
				} while (!found);
				
				item += restOfItem;
				lastCharacterPos = item.length();
			}

			item = item.substr(1, lastCharacterPos - 1);
		}

		result.push_back(item);
	}
}