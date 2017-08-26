#ifndef __KEYCODETOSTRING_H__
#define __KEYCODETOSTRING_H__

#include <string>
#include <map>
#include "input/KeyCodes.h"

namespace Niski
{
	namespace Input
	{
		class KeyCodeToString
		{
		public:
			KeyCodeToString(void);
			~KeyCodeToString(void);

			const std::string	translate(KeyCodes keyCode) const;
			KeyCodes			translate(const std::string& keyString) const;

		private:
			std::map<KeyCodes, std::string> translations_;
		};
	}
}

#endif