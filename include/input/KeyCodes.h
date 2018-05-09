#ifndef __INPUT_KEYCODES_H__
#define __INPUT_KEYCODES_H__

#include "SDL/SDL.h"

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
			Key_App,
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
			Key_F13,
			Key_F14,
			Key_F15,
			Key_F16,
			Key_F17,
			Key_F18,
			Key_F19,
			Key_F20,
			Key_F21,
			Key_F22,
			Key_F23,
			Key_F24,

			//
			// Application Control Keys
			Key_AC_Back,
			Key_AC_Forward,
			Key_AC_Home,
			Key_AC_Refresh,
			Key_AC_Stop,
			Key_AC_Bookmarks,

			//
			// Media Keys
			Key_Media_Mute,
			Key_Media_Next,
			Key_Media_Prev,
			Key_Media_Stop,
			Key_Media_Play,
			Key_VolumeUp,
			Key_VolumeDown,

			Mouse_InvalidButton,

			//
			// Mouse buttons
			Mouse_LeftButton,
			Mouse_RightButton,
			Mouse_MiddleButton,
			Mouse_Side_Forward,
			Mouse_Side_Backward
		};

		inline KeyCodes ConvertSDLToMouseButton(int8_t btn)
		{
			switch (btn)
			{
			case SDL_BUTTON_LEFT: return Mouse_LeftButton;
			case SDL_BUTTON_RIGHT: return Mouse_RightButton;
			case SDL_BUTTON_MIDDLE: return Mouse_MiddleButton;
			case SDL_BUTTON_X1: return Mouse_Side_Forward;
			case SDL_BUTTON_X2: return Mouse_Side_Backward;
			default: return Mouse_InvalidButton;
			}
		}

		inline KeyCodes ConvertSDLKeyToKeyCode(SDL_Keycode k)
		{
			switch (k)
			{
			case SDLK_0: return Key_0;
			case SDLK_1: return Key_1;
			case SDLK_2: return Key_2;
			case SDLK_3: return Key_3;
			case SDLK_4: return Key_4;
			case SDLK_5: return Key_5;
			case SDLK_6: return Key_6;
			case SDLK_7: return Key_7;
			case SDLK_8: return Key_8;
			case SDLK_9: return Key_9;

			case SDLK_AC_BACK: return Key_AC_Back;
			case SDLK_AC_FORWARD: return Key_AC_Forward;
			case SDLK_AC_HOME: return Key_AC_Home;
			case SDLK_AC_REFRESH: return Key_AC_Refresh;
			case SDLK_AC_STOP: return Key_AC_Stop;
			case SDLK_AC_BOOKMARKS: return Key_AC_Bookmarks;

			case SDLK_a: return	Key_A;
			case SDLK_b: return	Key_B;
			case SDLK_c: return Key_C;
			case SDLK_d: return Key_D;
			case SDLK_e: return Key_E;
			case SDLK_f: return Key_F;
			case SDLK_g: return Key_G;
			case SDLK_h: return Key_H;
			case SDLK_i: return Key_I;
			case SDLK_j: return Key_J;
			case SDLK_k: return Key_K;
			case SDLK_l: return Key_L;
			case SDLK_m: return Key_M;
			case SDLK_n: return Key_N;
			case SDLK_o: return Key_O;
			case SDLK_p: return Key_P;
			case SDLK_q: return Key_Q;
			case SDLK_r: return Key_R;
			case SDLK_s: return Key_S;
			case SDLK_t: return Key_T;
			case SDLK_u: return Key_U;
			case SDLK_v: return Key_V;
			case SDLK_w: return Key_W;
			case SDLK_x: return Key_X;
			case SDLK_y: return Key_Y;
			case SDLK_z: return Key_Z;

			case SDLK_KP_0: return Key_Pad_0;
			case SDLK_KP_1: return Key_Pad_1;
			case SDLK_KP_2: return Key_Pad_2;
			case SDLK_KP_3: return Key_Pad_3;
			case SDLK_KP_4: return Key_Pad_4;
			case SDLK_KP_5: return Key_Pad_5;
			case SDLK_KP_6: return Key_Pad_6;
			case SDLK_KP_7: return Key_Pad_7;
			case SDLK_KP_8: return Key_Pad_8;
			case SDLK_KP_9: return Key_Pad_9;
			case SDLK_KP_DIVIDE: return Key_Pad_Divide;
			case SDLK_KP_MULTIPLY: return Key_Pad_Multiply;
			case SDLK_KP_MINUS: return Key_Pad_Minus;
			case SDLK_KP_PLUS: return Key_Pad_Plus;
			case SDLK_KP_ENTER: return Key_Pad_Enter;
			case SDLK_KP_DECIMAL: return Key_Pad_Decimal;
			case SDLK_NUMLOCKCLEAR: return Key_Pad_NumLock;

			case SDLK_F1: return Key_F1;
			case SDLK_F2: return Key_F2;
			case SDLK_F3: return Key_F3;
			case SDLK_F4: return Key_F4;
			case SDLK_F5: return Key_F5;
			case SDLK_F6: return Key_F6;
			case SDLK_F7: return Key_F7;
			case SDLK_F8: return Key_F8;
			case SDLK_F9: return Key_F9;
			case SDLK_F10: return Key_F10;
			case SDLK_F11: return Key_F11;
			case SDLK_F12: return Key_F12;
			case SDLK_F13: return Key_F13;
			case SDLK_F14: return Key_F14;
			case SDLK_F15: return Key_F15;
			case SDLK_F16: return Key_F16;
			case SDLK_F17: return Key_F17;
			case SDLK_F18: return Key_F18;
			case SDLK_F19: return Key_F19;
			case SDLK_F20: return Key_F20;
			case SDLK_F21: return Key_F21;
			case SDLK_F22: return Key_F22;
			case SDLK_F23: return Key_F23;
			case SDLK_F24: return Key_F24;

			case SDLK_RIGHTBRACKET: return Key_RightBracket;
			case SDLK_LEFTBRACKET: return Key_LeftBracket;
			case SDLK_SEMICOLON: return Key_Semicolon;
			case SDLK_QUOTE: return Key_Apostrophe;
			case SDLK_COMMA: return Key_Comma;
			case SDLK_PERIOD: return Key_Period;
			case SDLK_SLASH: return Key_Slash;
			case SDLK_BACKSLASH: return Key_BackSlash;
			case SDLK_MINUS: return Key_Minus;
			case SDLK_EQUALS: return Key_Equal;
			case SDLK_RETURN: return Key_Enter;
			case SDLK_SPACE: return Key_Space;
			case SDLK_BACKSPACE: return Key_BackSpace;
			case SDLK_TAB: return Key_Tab;
			case SDLK_CAPSLOCK: return Key_CapsLock;
			case SDLK_ESCAPE: return Key_Escape;
			case SDLK_BACKQUOTE: return Key_BackQuote;
			case SDLK_PRINTSCREEN: return Key_Snapshot;
			case SDLK_SCROLLLOCK: return Key_ScrollLock;
			case SDLK_PAUSE: return Key_Break;
			case SDLK_INSERT: return Key_Insert;
			case SDLK_DELETE: return Key_Delete;
			case SDLK_HOME: return Key_Home;
			case SDLK_END: return Key_End;
			case SDLK_PAGEUP: return Key_PageUp;
			case SDLK_PAGEDOWN: return Key_PageDown;
			case SDLK_LSHIFT: return Key_LeftShift;
			case SDLK_RSHIFT: return Key_RightShift;
			case SDLK_LALT: return Key_LeftAlt;
			case SDLK_RALT: return Key_RightAlt;
			case SDLK_APPLICATION: return Key_App;
			case SDLK_LGUI: return Key_LeftWin;
			case SDLK_RGUI: return Key_RightWin;
			case SDLK_UP: return Key_Up;
			case SDLK_DOWN: return Key_Down;
			case SDLK_RIGHT: return Key_Right;
			case SDLK_LEFT: return Key_Left;

			case SDLK_AUDIOMUTE: return Key_Media_Mute;
			case SDLK_AUDIONEXT: return Key_Media_Next;
			case SDLK_AUDIOPREV: return Key_Media_Prev;
			case SDLK_AUDIOSTOP: return Key_Media_Stop;
			case SDLK_AUDIOPLAY: return Key_Media_Play;
			case SDLK_VOLUMEUP: return Key_VolumeUp;
			case SDLK_VOLUMEDOWN: return Key_VolumeDown;
				
			//
			// There are more keys than would be valuable for us to support. 
			default: return Key_InvalidKey;
			}
		}
	}
}

#endif