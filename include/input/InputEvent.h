#ifndef __INPUT_INPUTEVENT_H__
#define __INPUT_INPUTEVENT_H__

#include "input/KeyCodes.h"

namespace Niski
{
	namespace Input
	{
		class InputEvent
		{
		public:
			enum KeyState
			{
				Pressed = 0,
				Released
			};

		public:
			// TODO stateChanged might be unnecessary
			InputEvent(KeyCodes key, KeyState state, double stateChanged);
			~InputEvent(void);

			Niski::Input::KeyCodes	getKeyCode(void)			const;
			KeyState				getKeyState(void)			const;
			double					getTimeStateChanged(void)	const;

		private:
			KeyCodes	key_;
			KeyState	state_;
			double		stateChanged_;
		};
	}
}

#endif