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

std::string Win32::getDataDirectory(void)
{
	char path[MAX_PATH];
	HRESULT result = ::SHGetFolderPathA(nullptr, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, nullptr, SHGFP_TYPE_CURRENT, path);

	Niski::Utils::Assert(result == S_OK, "Failed to get folder path to user's \"My Documents\" folder", __FILE__, __FUNCSIG__, __LINE__);

	//
	// Do we need to create these folders prior?
	::PathAppendA(path, "My Games");

	if(::PathFileExistsA(path) == FALSE)
	{
		bool ret = createFolder(path);

		//
		// TODO: just continue ... ?
		if(ret == false)
		{
			Niski::Utils::error("Failed to create the \"My Games\" folder in the user's \"My Documents\" folder");
		}
	}

	::PathAppendA(path, "Niski Engine");

	if(::PathFileExistsA(path) == FALSE)
	{
		bool ret = createFolder(path);

		//
		// TODO: just continue ... ?
		if(ret == false)
		{
			Niski::Utils::error("Failed to create the \"Niski Engine\" folder in the user's \"My Documents\" folder");

			return path;
		}

		//
		// Make our directory structure in the data folder.. kinda hacky. 
		// TODO: There should be a way to specify what folders you need... as well as 
		// the ability to change the name of the game folder.. 
		std::vector<std::string> folders;
		folders.push_back("config");
		folders.push_back("logs");
		folders.push_back("saves");

		for(auto folder : folders)
		{
			char tempPath[MAX_PATH];
			strcpy_s(tempPath, MAX_PATH, path);

			::PathAppendA(tempPath, folder.c_str());

			if(::PathFileExistsA(tempPath) == FALSE)
			{
				createFolder(tempPath);
			}
		}
	}

	return path;
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