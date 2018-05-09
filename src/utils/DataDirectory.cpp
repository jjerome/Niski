#include "utils/DataDirectory.h"
#include <direct.h>

using namespace Niski::Utils;

//
// Initialize our static variable.
// Not sure if having this as a static variable is good karma. 
DataDirectory* DataDirectory::dir = nullptr;


DataDirectory::DataDirectory(const std::string& gameName) : gameName_(gameName)
{
	//
	// initialize our member.
	::ZeroMemory(path_, MAX_PATH * sizeof(char));

	HRESULT result = ::SHGetFolderPathA(nullptr, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, nullptr, SHGFP_TYPE_CURRENT, path_);

	//
	// TODO: More descriptive error text (GetLastError)
	Niski::Utils::Assert(result == S_OK, "Failed to get folder path to user's documents folder", __FILE__, __FUNCSIG__, __LINE__);

	//
	// Check if the "My Games" path exists, if not, create it
	::PathAppendA(path_, "My Games");

	if(pathExists(path_, pathExistsAction::create) == pathExistsResponse::pathDoesNotExist_FailedToCreate)
	{
		//
		// TODO: More descriptive error text.. 
		Niski::Utils::Assert(false, "\"My Games\" directory does not exist and we failed to create one", __FILE__, __FUNCSIG__, __LINE__);
	}

	//
	// Now check if %user%\documents\my games\<game name> exists and create it, if it doesn't
	::PathAppendA(path_, gameName_.data());

	if(pathExists(path_, pathExistsAction::create) == pathExistsResponse::pathDoesNotExist_FailedToCreate)
	{
		//
		// TODO: More descriptive error text
		std::ostringstream err;
		err << "Failed to create path: " << path_;
		Niski::Utils::Assert(false, err.str(), __FILE__, __FUNCSIG__, __LINE__);
	}

}

DataDirectory::~DataDirectory(void)
{}

const std::string DataDirectory::getPath(const std::string& folderName) const
{
	char tempPath[MAX_PATH];
	strcpy_s(tempPath, MAX_PATH, path_);

	::PathAppendA(tempPath, folderName.data());

	if(pathExists(tempPath, pathExistsAction::create) == pathExistsResponse::pathDoesNotExist_FailedToCreate)
	{
		//
		// TODO: More descriptive error text..
		// This should also be an exception provided we know it's not a fuck up
		// on our end (e.g. path_ wasn't valid to begin with)
		Niski::Utils::Assert(false, "Failed to create path", __FILE__, __FUNCSIG__, __LINE__);

		return "INVALID_PATH";
	}

	return std::string(tempPath);
}

DataDirectory::pathExistsResponse DataDirectory::pathExists(const std::string& path, pathExistsAction action /* = create */) const
{
	//
	// Check if a path exists. It's possible for PathFileExists to lie, initially.
	// So we attempt it twice, with a period of 1ms in between to verify. (It only lies
	// that it doesn't exist, so if it reports that it does exist initially, we can skip 
	// the second attempt)

	int8_t tries = 1;
	BOOL result;

	do 
	{
		result = ::PathFileExistsA(path.data());
		
		if(result == TRUE)
		{
			break;
		}

		::Sleep(1);
	} while (tries > 0 && tries--);

	if(result == FALSE)
	{
		//
		// Attempt to create it, if we're allowed. 
		if(action == pathExistsAction::create)
		{
			if(_mkdir(path.data()) == -1)
			{
				return pathExistsResponse::pathDoesNotExist_FailedToCreate;
			}
		}
		else
		{
			return pathExistsResponse::pathDoesNotExist;
		}
	}

	return pathExistsResponse::pathDoesExist;
}