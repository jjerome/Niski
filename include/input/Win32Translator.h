#ifndef __INPUT_WIN32CODES_H__
#define __INPUT_WIN32CODES_H__

#if defined(_WIN32) || defined(_WIN64)
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#endif
#include "input/KeyCodes.h"
#include <cstdint>

namespace Niski
{
	namespace Input
	{
		class Win32Translator
		{
		public:
			Win32Translator(void);
			~Win32Translator(void);

			KeyCodes translate(uint64_t key) const;
			KeyCodes mouseTranslate(uint64_t key) const;
		private:
			uint64_t win32TranslationTable[255];
			uint64_t win32MouseTranslationTable[65];
		};
	}
}

#endif