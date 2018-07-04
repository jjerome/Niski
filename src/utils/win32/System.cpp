//
// Standard headers
#include <string>
#include <vector>

//
// Windows only headers
#include <Windows.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <direct.h>

#include "utils/Win32/System.h"
#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Utils;

Niski::Math::Vector2D<int32_t> Win32::getDesktopResolution(void)
{
	Niski::Math::Vector2D<int32_t> resolution(0, 0);

	resolution.x = ::GetSystemMetrics(SM_CXSCREEN);
	resolution.y = ::GetSystemMetrics(SM_CYSCREEN);

	return resolution;
}

bool createFolder(const std::string& path)
{
	return _mkdir(path.c_str()) != -1;
}

std::string Win32::getErrorString(DWORD messageID)
{
	LPSTR buffer = nullptr;

	::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		messageID,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		buffer,
		0,
		nullptr);

	std::string result(buffer);

	// Free the buffer that it allocated, since we copied it already
	::LocalFree(buffer);

	return result;
}