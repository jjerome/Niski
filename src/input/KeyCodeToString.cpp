#include "input/KeyCodeToString.h"

using namespace Niski::Input;

KeyCodeToString::KeyCodeToString(void)
{
	//
	// Alphabet
	translations_[Key_A] = "a";
	translations_[Key_B] = "b";
	translations_[Key_C] = "c";
	translations_[Key_D] = "d";
	translations_[Key_E] = "e";
	translations_[Key_F] = "f";
	translations_[Key_G] = "g";
	translations_[Key_H] = "h";
	translations_[Key_I] = "i";
	translations_[Key_J] = "j";
	translations_[Key_K] = "k";
	translations_[Key_L] = "l";
	translations_[Key_M] = "m";
	translations_[Key_N] = "n";
	translations_[Key_O] = "o";
	translations_[Key_P] = "p";
	translations_[Key_Q] = "q";
	translations_[Key_R] = "r";
	translations_[Key_S] = "s";
	translations_[Key_T] = "t";
	translations_[Key_U] = "u";
	translations_[Key_V] = "v";
	translations_[Key_W] = "w";
	translations_[Key_X] = "x";
	translations_[Key_Y] = "y";
	translations_[Key_Z] = "z";

	//
	// Number row
	translations_[Key_0] = "0";
	translations_[Key_1] = "1";
	translations_[Key_2] = "2";
	translations_[Key_3] = "3";
	translations_[Key_4] = "4";
	translations_[Key_5] = "5";
	translations_[Key_6] = "6";
	translations_[Key_7] = "7";
	translations_[Key_8] = "8";
	translations_[Key_9] = "9";

	//
	// Key pad
	translations_[Key_Pad_0] = "kp_0";
	translations_[Key_Pad_1] = "kp_1";
	translations_[Key_Pad_2] = "kp_2";
	translations_[Key_Pad_3] = "kp_3";
	translations_[Key_Pad_4] = "kp_4";
	translations_[Key_Pad_5] = "kp_5";
	translations_[Key_Pad_6] = "kp_6";
	translations_[Key_Pad_7] = "kp_7";
	translations_[Key_Pad_8] = "kp_8";
	translations_[Key_Pad_9] = "kp_9";

	//
	// Key pad keys
	translations_[Key_Pad_Divide] = "kp_/";
	translations_[Key_Pad_Multiply] = "kp_*";
	translations_[Key_Pad_Minus] = "kp_-";
	translations_[Key_Pad_Plus] = "kp_+";
	translations_[Key_Pad_Enter] = "kp_enter";
	translations_[Key_Pad_Decimal] = "kp_.";
	translations_[Key_Pad_NumLock] = "kp_numlock";

	//
	// Other keys..
	translations_[Key_LeftBracket] = "[";
	translations_[Key_RightBracket] = "]";
	translations_[Key_Semicolon] = ";";
	translations_[Key_Apostrophe] = "'";
	translations_[Key_Comma] = ",";
	translations_[Key_Period] = ".";
	translations_[Key_Slash] = "/";
	translations_[Key_BackSlash] = "\\";
	translations_[Key_Minus] = "-";
	translations_[Key_Equal] = "=";
	translations_[Key_Enter] = "enter";
	translations_[Key_Space] = "space";
	translations_[Key_BackSpace] = "backspace";
	translations_[Key_Tab] = "tab";
	translations_[Key_CapsLock] = "capslock";
	translations_[Key_Escape] = "escape";
	translations_[Key_BackQuote] = "`";
	translations_[Key_Snapshot] = "snapshot";
	translations_[Key_ScrollLock] = "scrolllock";
	translations_[Key_Break] = "break";
	translations_[Key_Insert] = "insert";
	translations_[Key_Delete] = "delete";
	translations_[Key_Home] = "home";
	translations_[Key_End] = "end";
	translations_[Key_PageUp] = "pageup";
	translations_[Key_PageDown] = "pagedown";
	translations_[Key_LeftShift] = "lshift";
	translations_[Key_RightShift] = "rshift";
	translations_[Key_LeftAlt] = "lalt";
	translations_[Key_RightAlt] = "ralt";
	translations_[Key_LeftControl] = "lctrl";
	translations_[Key_RightControl] = "rctrl";
	translations_[Key_LeftWin] = "lwin";
	translations_[Key_RightWin] = "rwin";
	translations_[Key_Up] = "up";
	translations_[Key_Down] = "down";
	translations_[Key_Left] = "left";
	translations_[Key_Right] = "right";
	
	//
	// Function keys 
	translations_[Key_F1] = "f1";
	translations_[Key_F2] = "f2";
	translations_[Key_F3] = "f3";
	translations_[Key_F4] = "f4";
	translations_[Key_F5] = "f5";
	translations_[Key_F6] = "f6";
	translations_[Key_F7] = "f7";
	translations_[Key_F8] = "f8";
	translations_[Key_F9] = "f9";
	translations_[Key_F10] = "f10";
	translations_[Key_F11] = "f11";
	translations_[Key_F12] = "f12";

	//
	// Mouse buttons
	translations_[Mouse_LeftButton] = "mouse_lb";
	translations_[Mouse_RightButton] = "mouse_rb";
	translations_[Mouse_MiddleButton] = "mouse_mb";
	translations_[Mouse_Side_Forward] = "mouse_side_forward";
	translations_[Mouse_Side_Backward] = "mouse_side_backward";
}

KeyCodeToString::~KeyCodeToString(void)
{}

const std::string KeyCodeToString::translate(KeyCodes keyCode) const
{
	return translations_.at(keyCode);
}

KeyCodes KeyCodeToString::translate(const std::string& keyString) const
{
	for(auto key : translations_)
	{
		if(keyString == key.second)
		{
			return key.first;
		}
	}

	return Key_InvalidKey;
}
