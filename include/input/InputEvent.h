#ifndef __INPUT_INPUTEVENT_H__
#define __INPUT_INPUTEVENT_H__

#include "input/KeyCodes.h"

namespace Niski
{
	namespace Input
	{

		enum KeyState
		{
			Pressed = 0,
			Released
		};

		class InputEvent
		{
		public:
			// TODO stateChanged might be unnecessary
			InputEvent(KeyCodes key, KeyState state, uint32_t when);
			~InputEvent(void);

			Niski::Input::KeyCodes	getKeyCode(void)			const;
			KeyState				getKeyState(void)			const;
			uint32_t					when(void)	const;

		private:
			KeyCodes	key_;
			KeyState	state_;
			uint32_t		when_;
		};

		class MouseBtnEvent
		{
		public:
			MouseBtnEvent(KeyCodes btn, KeyState state, uint32_t when) : btn_(btn), state_(state), when_(when) {}

			KeyCodes getButton(void) const
			{
				return btn_;
			}

			KeyState getState(void) const
			{
				return state_;
			}

			uint32_t getWhen(void) const
			{
				return when_;
			}

		private:
			KeyCodes btn_;
			KeyState state_;
			uint32_t when_;
		};
	}
}

#endif