
//
// Native functions for Pawn..
#include <string>
#include <memory>
#include <sstream>

#include "amx.h"

//
// Helper functions.
inline std::string getStringFromCell(AMX* amx, cell* param)
{
	int length;
	amx_StrLen(param, &length);

	//
	// Allocate the memory we need.. 
	std::unique_ptr<char[]> data(new char[length]);

	amx_GetString(data.get(), param, 0, length + 1);

	return std::string(data.get());
}

inline std::wstring getWStringFromCell(AMX* amx, cell* param)
{
	int length;
	amx_StrLen(param, &length);

	//
	// Allocate the memory we need.. 
	std::unique_ptr<char[]> data(new char[length]);

	//
	// data cannot be wchar_t? Not sure if this works..
	amx_GetString(data.get(), param, 1, length + 1);

	//
	// Hacky as fuck...
	std::wostringstream ss;
	ss << data;

	return ss.str();
}