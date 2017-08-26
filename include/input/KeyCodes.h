#ifndef __INPUT_KEYCODES_H__
#define __INPUT_KEYCODES_H__
//
// Internal key codes - input system translates them for us from host OS'
namespace Niski
{
	namespace Input
	{
		enum KeyCodes
		{
			//
			// Invalid key code..
			Key_InvalidKey = 0,

			//
			// Alpha keys
			Key_A,
			Key_B, 
			Key_C,
			Key_D,
			Key_E,
			Key_F,
			Key_G,
			Key_H, 
			Key_I,
			Key_J,
			Key_K,
			Key_L,
			Key_M,
			Key_N,
			Key_O,
			Key_P,
			Key_Q,
			Key_R,
			Key_S,
			Key_T,
			Key_U,
			Key_V,
			Key_W,
			Key_X,
			Key_Y,
			Key_Z,

			//
			// Number row
			Key_0,
			Key_1,
			Key_2,
			Key_3,
			Key_4,
			Key_5,
			Key_6,
			Key_7,
			Key_8,
			Key_9,

			//
			// Key Pad
			Key_Pad_0,
			Key_Pad_1,
			Key_Pad_2,
			Key_Pad_3,
			Key_Pad_4,
			Key_Pad_5,
			Key_Pad_6,
			Key_Pad_7,
			Key_Pad_8,
			Key_Pad_9,
			Key_Pad_Divide,
			Key_Pad_Multiply,
			Key_Pad_Minus,
			Key_Pad_Plus,
			Key_Pad_Enter,
			Key_Pad_Decimal,
			Key_Pad_NumLock,

			//
			// Other keys
			Key_LeftBracket,
			Key_RightBracket,
			Key_Semicolon,
			Key_Apostrophe,
			Key_Comma,
			Key_Period,
			Key_Slash,
			Key_BackSlash,
			Key_Minus,
			Key_Equal,
			Key_Enter,
			Key_Space,
			Key_BackSpace,
			Key_Tab,
			Key_CapsLock,
			Key_Escape,
			Key_BackQuote,
			Key_Snapshot,
			Key_ScrollLock,
			Key_Break,
			Key_Insert,
			Key_Delete,
			Key_Home,
			Key_End,
			Key_PageUp,
			Key_PageDown,
			Key_LeftShift,
			Key_RightShift,
			Key_LeftAlt,
			Key_RightAlt,
			Key_LeftControl,
			Key_RightControl,
			Key_LeftWin,
			Key_RightWin,
			Key_Up,
			Key_Down,
			Key_Left,
			Key_Right,

			//
			// Function Keys
			Key_F1,
			Key_F2,
			Key_F3,
			Key_F4,
			Key_F5,
			Key_F6,
			Key_F7,
			Key_F8,
			Key_F9,
			Key_F10,
			Key_F11,
			Key_F12,

			//
			// Mouse buttons
			Mouse_LeftButton,
			Mouse_RightButton,
			Mouse_MiddleButton,
			Mouse_Side_Forward,
			Mouse_Side_Backward,

			Mouse_Wheel_Down,
			Mouse_Wheel_Up
		};
	}
}

#endif