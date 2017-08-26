#ifndef __UTILS_DATADIRECTORY_H__
#define __UTILS_DATADIRECTORY_H__

#include <string>
#include <sstream>

#include "utils/Assert.h"
#include "utils/win32/Win32Includes.h"

/*
===============================================================================

	Provides access to a writable directory (on Windows this directory is
	%user%\My Documents\My Games\<gameName>\)

===============================================================================
*/

//
// We need to define this for the static variable.

namespace Niski
{
	namespace Utils
	{
		class DataDirectory
		{
		public:
			enum pathExistsAction
			{
				//
				// Don't like these names..
				nothing,
				create,
			};

			enum pathExistsResponse
			{
				pathDoesNotExist = 0,
				//
				// TODO: This is ugly as fuck, should we return flags instead
				// or maybe this should just be renamed to "FailedToCreate" since
				// it's heavily implied that the path doesn't exist. 
				pathDoesNotExist_FailedToCreate,
				pathDoesExist,
			};

		public:
			static void openDataDirectory(const std::wstring& gameName) { dir = new DataDirectory(gameName); }
			static DataDirectory* getDataDirectory() {
				Niski::Utils::Assert(dir != nullptr, "Tried to get the writable directory before it was initialized.", __FILE__, __FUNCSIG__, __LINE__);
				return dir;
			}

		private:
			static DataDirectory* dir;

		public:
			DataDirectory(const std::wstring& gameName);
			~DataDirectory(void);

			//
			// Returns the proper path of %user%/My Documents/My Games/<game name>/<folder name>
			// also guarantees that the path exists
			// NOTE: this doesn't cache results so repeatedly calling it
			// is ill-advised. 
			const std::wstring getPath(const std::wstring& folderName) const;

		private:
			pathExistsResponse pathExists(const std::wstring& path, pathExistsAction action = create) const;

		private:
			std::wstring gameName_;
			wchar_t path_[MAX_PATH];
		};
	}
}

#endif