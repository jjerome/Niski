#ifndef __INPUT_CHARLISTENER_H__
#define __INPUT_CHARLISTENER_H__

#include <string>

namespace Niski
{
	namespace Input
	{
		class CharListener
		{
		public:
			virtual void receiveTextInput(std::string str) = 0;
		};
	}
}

#endif