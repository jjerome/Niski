#include "input/InputEvent.h"

using namespace Niski::Input;

InputEvent::InputEvent(KeyCodes key, KeyState state, uint32_t when) : key_(key), state_(state), when_(when)
{}

InputEvent::~InputEvent(void)
{}

Niski::Input::KeyCodes InputEvent::getKeyCode(void) const
{
	return key_;
}

KeyState InputEvent::getKeyState(void) const
{
	return state_;
}

uint32_t InputEvent::when(void) const
{
	return when_;
}