#ifndef __UTILS_WIN32_SYSTEM_H__
#define __UTILS_WIN32_SYSTEM_H__

#include "math/Vec2d.h"
#include "Win32Includes.h"
#include <cstdint>
#include <string>

namespace Niski
{
	namespace Utils
	{
		namespace Win32
		{
			Niski::Math::Vector2D<int32_t> getDesktopResolution(void);
			std::string getDataDirectory(void);
			std::string getErrorString(DWORD messageID);
		}
	}
}

#endif