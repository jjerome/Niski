#ifndef __KEYCODETOSTRING_H__
#define __KEYCODETOSTRING_H__

#include <string>
#include <unordered_map>
#include "input/KeyCodes.h"

namespace Niski
{
	namespace Input
	{
		inline std::string KeyCodeToString(KeyCodes kc)
		{
			switch (kc)
			{
				//
				// Alphabet
			case Key_A: return "a";
			case Key_B: return "b";
			case Key_C: return "c";
			case Key_D: return "d";
			case Key_E: return "e";
			case Key_F: return "f";
			case Key_G: return "g";
			case Key_H: return "h";
			case Key_I: return "i";
			case Key_J: return "j";
			case Key_K: return "k";
			case Key_L: return "l";
			case Key_M: return "m";
			case Key_N: return "n";
			case Key_O: return "o";
			case Key_P: return "p";
			case Key_Q: return "q";
			case Key_R: return "r";
			case Key_S: return "s";
			case Key_T: return "t";
			case Key_U: return "u";
			case Key_V: return "v";
			case Key_W: return "w";
			case Key_X: return "x";
			case Key_Y: return "y";
			case Key_Z: return "z";

				//
				// Number row
			case Key_0: return "0";
			case Key_1: return "1";
			case Key_2: return "2";
			case Key_3: return "3";
			case Key_4: return "4";
			case Key_5: return "5";
			case Key_6: return "6";
			case Key_7: return "7";
			case Key_8: return "8";
			case Key_9: return "9";

				//
				// Key pad
			case Key_Pad_0: return "kp_0";
			case Key_Pad_1: return "kp_1";
			case Key_Pad_2: return "kp_2";
			case Key_Pad_3: return "kp_3";
			case Key_Pad_4: return "kp_4";
			case Key_Pad_5: return "kp_5";
			case Key_Pad_6: return "kp_6";
			case Key_Pad_7: return "kp_7";
			case Key_Pad_8: return "kp_8";
			case Key_Pad_9: return "kp_9";

				//
				// Key pad keys
			case Key_Pad_Divide: return "kp_/";
			case Key_Pad_Multiply: return "kp_*";
			case Key_Pad_Minus: return "kp_-";
			case Key_Pad_Plus: return "kp_+";
			case Key_Pad_Enter: return "kp_enter";
			case Key_Pad_Decimal: return "kp_.";
			case Key_Pad_NumLock: return "kp_numlock";

				//
				// Other keys..
			case Key_LeftBracket: return "[";
			case Key_RightBracket: return "]";
			case Key_Semicolon: return ";";
			case Key_Apostrophe: return "'";
			case Key_Comma: return ",";
			case Key_Period: return ".";
			case Key_Slash: return "/";
			case Key_BackSlash: return "\\";
			case Key_Minus: return "-";
			case Key_Equal: return "=";
			case Key_Enter: return "enter";
			case Key_Space: return "space";
			case Key_BackSpace: return "backspace";
			case Key_Tab: return "tab";
			case Key_CapsLock: return "capslock";
			case Key_Escape: return "escape";
			case Key_BackQuote: return "`";
			case Key_Snapshot: return "snapshot";
			case Key_ScrollLock: return "scrolllock";
			case Key_Break: return "break";
			case Key_Insert: return "insert";
			case Key_Delete: return "delete";
			case Key_Home: return "home";
			case Key_End: return "end";
			case Key_PageUp: return "pageup";
			case Key_PageDown: return "pagedown";
			case Key_LeftShift: return "lshift";
			case Key_RightShift: return "rshift";
			case Key_LeftAlt: return "lalt";
			case Key_RightAlt: return "ralt";
			case Key_LeftControl: return "lctrl";
			case Key_RightControl: return "rctrl";
			case Key_App: return "app";
			case Key_LeftWin: return "lwin";
			case Key_RightWin: return "rwin";
			case Key_Up: return "up";
			case Key_Down: return "down";
			case Key_Left: return "left";
			case Key_Right: return "right";

				//
				// Function keys 
			case Key_F1: return "f1";
			case Key_F2: return "f2";
			case Key_F3: return "f3";
			case Key_F4: return "f4";
			case Key_F5: return "f5";
			case Key_F6: return "f6";
			case Key_F7: return "f7";
			case Key_F8: return "f8";
			case Key_F9: return "f9";
			case Key_F10: return "f10";
			case Key_F11: return "f11";
			case Key_F12: return "f12";
			case Key_F13: return "f13";
			case Key_F14: return "f14";
			case Key_F15: return "f15";
			case Key_F16: return "f16";
			case Key_F17: return "f17";
			case Key_F18: return "f18";
			case Key_F19: return "f19";
			case Key_F20: return "f20";
			case Key_F21: return "f21";
			case Key_F22: return "f22";
			case Key_F23: return "f23";
			case Key_F24: return "f24";

				//
				// Media Keys
			case Key_Media_Mute: return "media_mute";
			case Key_Media_Next: return "media_next";
			case Key_Media_Prev: return "media_prev";
			case Key_Media_Play: return "media_play";
			case Key_Media_Stop: return "media_stop";
			case Key_VolumeUp: return "volume_up";
			case Key_VolumeDown: return "volume_down";

				//
				// Application control keys
			case Key_AC_Back: return "ac_back";
			case Key_AC_Forward: return "ac_forward";
			case Key_AC_Home: return "ac_home";
			case Key_AC_Refresh: return "ac_refresh";
			case Key_AC_Stop: return "ac_stop";
			case Key_AC_Bookmarks: return "ac_bookmarks";

				//
				// Mouse buttons
			case Mouse_LeftButton: return "mouse_lb";
			case Mouse_RightButton: return "mouse_rb";
			case Mouse_MiddleButton: return "mouse_mb";
			case Mouse_Side_Forward: return "mouse_side_forward";
			case Mouse_Side_Backward: return "mouse_side_backward";

			default:
				return "INVALID_KEYCODE";
			}
		}

		KeyCodes StringToKeyCode(const std::string& str)
		{
			static std::unordered_map<std::string, KeyCodes> translations_;

			if (translations_.empty())
			{
				//
				// Alphabet
				translations_["a"] = Key_A;
				translations_["b"] = Key_B;
				translations_["c"] = Key_C;
				translations_["d"] = Key_D;
				translations_["e"] = Key_E;
				translations_["f"] = Key_F;
				translations_["g"] = Key_G;
				translations_["h"] = Key_H;
				translations_["i"] = Key_I;
				translations_["j"] = Key_J;
				translations_["k"] = Key_K;
				translations_["l"] = Key_L;
				translations_["m"] = Key_M;
				translations_["n"] = Key_N;
				translations_["o"] = Key_O;
				translations_["p"] = Key_P;
				translations_["q"] = Key_Q;
				translations_["r"] = Key_R;
				translations_["s"] = Key_S;
				translations_["t"] = Key_T;
				translations_["u"] = Key_U;
				translations_["v"] = Key_V;
				translations_["w"] = Key_W;
				translations_["x"] = Key_X;
				translations_["y"] = Key_Y;
				translations_["z"] = Key_Z;

				//
				// Number row
				translations_["0"] = Key_0;
				translations_["1"] = Key_1;
				translations_["2"] = Key_2;
				translations_["3"] = Key_3;
				translations_["4"] = Key_4;
				translations_["5"] = Key_5;
				translations_["6"] = Key_6;
				translations_["7"] = Key_7;
				translations_["8"] = Key_8;
				translations_["9"] = Key_9;

				//
				// Key pad
				translations_["kp_0"] = Key_Pad_0;
				translations_["kp_1"] = Key_Pad_1;
				translations_["kp_2"] = Key_Pad_2;
				translations_["kp_3"] = Key_Pad_3;
				translations_["kp_4"] = Key_Pad_4;
				translations_["kp_5"] = Key_Pad_5;
				translations_["kp_6"] = Key_Pad_6;
				translations_["kp_7"] = Key_Pad_7;
				translations_["kp_8"] = Key_Pad_8;
				translations_["kp_9"] = Key_Pad_9;

				//
				// Key pad keys
				translations_["kp_/"] = Key_Pad_Divide;
				translations_["kp_*"] = Key_Pad_Multiply;
				translations_["kp_-"] = Key_Pad_Minus;
				translations_["kp_+"] = Key_Pad_Plus;
				translations_["kp_enter"] = Key_Pad_Enter;
				translations_["kp_."] = Key_Pad_Decimal;
				translations_["kp_numlock"] = Key_Pad_NumLock;

				//
				// Other keys..
				translations_["["] = Key_LeftBracket;
				translations_["]"] = Key_RightBracket;
				translations_[";"] = Key_Semicolon;
				translations_["'"] = Key_Apostrophe;
				translations_[","] = Key_Comma;
				translations_["."] = Key_Period;
				translations_["/"] = Key_Slash;
				translations_["\\"] = Key_BackSlash;
				translations_["-"] = Key_Minus;
				translations_["="] = Key_Equal;
				translations_["enter"] = Key_Enter;
				translations_["space"] = Key_Space;
				translations_["backspace"] = Key_BackSpace;
				translations_["tab"] = Key_Tab;
				translations_["capslock"] = Key_CapsLock;
				translations_["escape"] = Key_Escape;
				translations_["`"] = Key_BackQuote;
				translations_["snapshot"] = Key_Snapshot;
				translations_["scrolllock"] = Key_ScrollLock;
				translations_["break"] = Key_Break;
				translations_["insert"] = Key_Insert;
				translations_["delete"] = Key_Delete;
				translations_["home"] = Key_Home;
				translations_["end"] = Key_End;
				translations_["pageup"] = Key_PageUp;
				translations_["pagedown"] = Key_PageDown;
				translations_["lshift"] = Key_LeftShift;
				translations_["rshift"] = Key_RightShift;
				translations_["lalt"] = Key_LeftAlt;
				translations_["ralt"] = Key_RightAlt;
				translations_["lctrl"] = Key_LeftControl;
				translations_["rctrl"] = Key_RightControl;
				translations_["app"] = Key_App;
				translations_["lwin"] = Key_LeftWin;
				translations_["rwin"] = Key_RightWin;
				translations_["up"] = Key_Up;
				translations_["down"] = Key_Down;
				translations_["left"] = Key_Left;
				translations_["right"] = Key_Right;

				//
				// Function keys 
				translations_["f1"] = Key_F1;
				translations_["f2"] = Key_F2;
				translations_["f3"] = Key_F3;
				translations_["f4"] = Key_F4;
				translations_["f5"] = Key_F5;
				translations_["f6"] = Key_F6;
				translations_["f7"] = Key_F7;
				translations_["f8"] = Key_F8;
				translations_["f9"] = Key_F9;
				translations_["f10"] = Key_F10;
				translations_["f11"] = Key_F11;
				translations_["f12"] = Key_F12;
				translations_["f13"] = Key_F13;
				translations_["f14"] = Key_F14;
				translations_["f15"] = Key_F15;
				translations_["f16"] = Key_F16;
				translations_["f17"] = Key_F17;
				translations_["f18"] = Key_F18;
				translations_["f19"] = Key_F19;
				translations_["f20"] = Key_F20;
				translations_["f21"] = Key_F21;
				translations_["f22"] = Key_F22;
				translations_["f23"] = Key_F23;
				translations_["f24"] = Key_F24;

				//
				// Media Keys
				translations_["media_mute"] = Key_Media_Mute;
				translations_["media_next"] = Key_Media_Next;
				translations_["media_prev"] = Key_Media_Prev;
				translations_["media_play"] = Key_Media_Play;
				translations_["media_stop"] = Key_Media_Stop;
				translations_["volume_up"] = Key_VolumeUp;
				translations_["volume_down"] = Key_VolumeDown;

				//
				// Application control keys
				translations_["ac_back"] = Key_AC_Back;
				translations_["ac_forward"] = Key_AC_Forward;
				translations_["ac_home"] = Key_AC_Home;
				translations_["ac_refresh"] = Key_AC_Refresh;
				translations_["ac_stop"] = Key_AC_Stop;
				translations_["ac_bookmarks"] = Key_AC_Bookmarks;

				//
				// Mouse buttons
				translations_["mouse_lb"] = Mouse_LeftButton;
				translations_["mouse_rb"] = Mouse_RightButton;
				translations_["mouse_mb"] = Mouse_MiddleButton;
				translations_["mouse_side_forward"] = Mouse_Side_Forward;
				translations_["mouse_side_backward"] = Mouse_Side_Backward;
			}

			auto entry = translations_.find(str);

			return (entry == translations_.end()) ? Key_InvalidKey : entry->second;
		}
	}
}

#endif