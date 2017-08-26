#include "input/Win32Translator.h"

using namespace Niski::Input;

Win32Translator::Win32Translator(void)
{
	//
	// Initialize the table...
	for(int i = 0; i < 256; ++i)
	{
		win32TranslationTable[i] = Key_InvalidKey;
	}

	for (int i = 0; i < 65; ++i)
	{
		win32MouseTranslationTable[i] = Key_InvalidKey;
	}

	//
	// Number row..
	win32TranslationTable['0'] = Key_0;
	win32TranslationTable['1'] = Key_1;
	win32TranslationTable['2'] = Key_2;
	win32TranslationTable['3'] = Key_3;
	win32TranslationTable['4'] = Key_4;
	win32TranslationTable['5'] = Key_5;
	win32TranslationTable['6'] = Key_6;
	win32TranslationTable['7'] = Key_7;
	win32TranslationTable['8'] = Key_8;
	win32TranslationTable['9'] = Key_9;

	//
	// Key pad..
	win32TranslationTable[VK_NUMPAD0] = Key_Pad_0;
	win32TranslationTable[VK_NUMPAD1] = Key_Pad_1;
	win32TranslationTable[VK_NUMPAD2] = Key_Pad_2;
	win32TranslationTable[VK_NUMPAD3] = Key_Pad_3;
	win32TranslationTable[VK_NUMPAD4] = Key_Pad_4;
	win32TranslationTable[VK_NUMPAD5] = Key_Pad_5;
	win32TranslationTable[VK_NUMPAD6] = Key_Pad_6;
	win32TranslationTable[VK_NUMPAD7] = Key_Pad_7;
	win32TranslationTable[VK_NUMPAD8] = Key_Pad_8;
	win32TranslationTable[VK_NUMPAD9] = Key_Pad_9;

	//
	// Key pad arithmetic buttons
	win32TranslationTable[VK_MULTIPLY] = Key_Pad_Multiply;
	win32TranslationTable[VK_ADD] = Key_Pad_Plus;
	win32TranslationTable[VK_SUBTRACT] = Key_Pad_Minus;
	win32TranslationTable[VK_DECIMAL] = Key_Pad_Decimal;
	win32TranslationTable[VK_DIVIDE] = Key_Pad_Divide;
	win32TranslationTable[VK_NUMLOCK] = Key_Pad_NumLock;

	//
	// F1 through F12
	win32TranslationTable[VK_F1] = Key_F1;
	win32TranslationTable[VK_F2] = Key_F2;
	win32TranslationTable[VK_F3] = Key_F3;
	win32TranslationTable[VK_F4] = Key_F4;
	win32TranslationTable[VK_F5] = Key_F5;
	win32TranslationTable[VK_F6] = Key_F6;
	win32TranslationTable[VK_F7] = Key_F7;
	win32TranslationTable[VK_F8] = Key_F8;
	win32TranslationTable[VK_F9] = Key_F9;
	win32TranslationTable[VK_F10] = Key_F10;
	win32TranslationTable[VK_F11] = Key_F11;
	win32TranslationTable[VK_F12] = Key_F12;

	//
	// A-Z
	win32TranslationTable['A'] = Key_A;
	win32TranslationTable['B'] = Key_B;
	win32TranslationTable['C'] = Key_C;
	win32TranslationTable['D'] = Key_D;
	win32TranslationTable['E'] = Key_E;
	win32TranslationTable['F'] = Key_F;
	win32TranslationTable['G'] = Key_G;
	win32TranslationTable['H'] = Key_H;
	win32TranslationTable['I'] = Key_I;
	win32TranslationTable['J'] = Key_J;
	win32TranslationTable['K'] = Key_K;
	win32TranslationTable['L'] = Key_L;
	win32TranslationTable['M'] = Key_M;
	win32TranslationTable['N'] = Key_N;
	win32TranslationTable['O'] = Key_O;
	win32TranslationTable['P'] = Key_P;
	win32TranslationTable['Q'] = Key_Q;
	win32TranslationTable['R'] = Key_R;
	win32TranslationTable['S'] = Key_S;
	win32TranslationTable['T'] = Key_T;
	win32TranslationTable['U'] = Key_U;
	win32TranslationTable['V'] = Key_V;
	win32TranslationTable['W'] = Key_W;
	win32TranslationTable['X'] = Key_X;
	win32TranslationTable['Y'] = Key_Y;
	win32TranslationTable['Z'] = Key_Z;

	//
	// Other misc keys
	win32TranslationTable[VK_LWIN] = Key_LeftWin;
	win32TranslationTable[VK_RWIN] = Key_RightWin;
	win32TranslationTable[VK_SCROLL] = Key_ScrollLock;
	win32TranslationTable[VK_SHIFT] = Key_LeftShift;
	win32TranslationTable[VK_RSHIFT] = Key_RightShift;
	win32TranslationTable[VK_CONTROL] = Key_LeftControl;
	win32TranslationTable[VK_RCONTROL] = Key_RightControl;
	win32TranslationTable[VK_LMENU] = Key_LeftAlt;
	win32TranslationTable[VK_MENU] = Key_LeftAlt; // The same as the above because they're two different codes for the same button.
												// TODO: Does this cause dupe key presses to go through?
	win32TranslationTable[VK_RMENU] = Key_RightAlt;
	win32TranslationTable[VK_OEM_1] = Key_Semicolon;
	win32TranslationTable[VK_OEM_PLUS] = Key_Equal;
	win32TranslationTable[VK_OEM_COMMA] = Key_Comma;
	win32TranslationTable[VK_OEM_MINUS] = Key_Minus;
	win32TranslationTable[VK_OEM_PERIOD] = Key_Period;
	win32TranslationTable[VK_OEM_2] = Key_Slash;
	win32TranslationTable[VK_OEM_3] = Key_BackQuote;
	win32TranslationTable[VK_OEM_4] = Key_LeftBracket;
	win32TranslationTable[VK_OEM_5] = Key_BackSlash;
	win32TranslationTable[VK_OEM_6] = Key_RightBracket;
	win32TranslationTable[VK_OEM_7] = Key_Apostrophe;
	win32TranslationTable[VK_BACK] = Key_BackSpace;
	win32TranslationTable[VK_TAB] = Key_Tab;
	win32TranslationTable[VK_RETURN] = Key_Enter;
	win32TranslationTable[VK_CAPITAL] = Key_CapsLock;
	win32TranslationTable[VK_SPACE] = Key_Space;
	win32TranslationTable[VK_ESCAPE] = Key_Escape;
	win32TranslationTable[VK_SNAPSHOT] = Key_Snapshot;
	win32TranslationTable[VK_PAUSE] = Key_Break;
	win32TranslationTable[VK_INSERT] = Key_Insert;
	win32TranslationTable[VK_DELETE] = Key_Delete;
	win32TranslationTable[VK_HOME] = Key_Home;
	win32TranslationTable[VK_END] = Key_End;
	win32TranslationTable[VK_PRIOR] = Key_PageUp;
	win32TranslationTable[VK_NEXT] = Key_PageDown;
	win32TranslationTable[VK_UP] = Key_Up;
	win32TranslationTable[VK_DOWN] = Key_Down;
	win32TranslationTable[VK_LEFT] = Key_Left;
	win32TranslationTable[VK_RIGHT] = Key_Right;

	//
	// Mouse buttons
	win32MouseTranslationTable[MK_LBUTTON] = Mouse_LeftButton;
	win32MouseTranslationTable[MK_RBUTTON] = Mouse_RightButton;
	win32MouseTranslationTable[MK_MBUTTON] = Mouse_MiddleButton;
	win32MouseTranslationTable[MK_XBUTTON1] = Mouse_Side_Backward;
	win32MouseTranslationTable[MK_XBUTTON2] = Mouse_Side_Forward;
}

Win32Translator::~Win32Translator(void)
{}

//
// TODO: Check bounds on this so we don't destroy ourselves 
// through a dumb mistake or some nonsense, even though it's 
// _incredibly_ unlikely at this point in time, better to 
// future-proof. 
KeyCodes Win32Translator::translate(uint64_t key) const
{
	return KeyCodes(win32TranslationTable[key]);
}

KeyCodes Win32Translator::mouseTranslate(uint64_t key) const
{
	return KeyCodes(win32MouseTranslationTable[key]);
}