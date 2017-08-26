#include "input/InputEvent.h"

using namespace Niski::Input;

InputEvent::InputEvent(KeyCodes key, KeyState state, double stateChanged) : key_(key), state_(state), stateChanged_(stateChanged)
{}

InputEvent::~InputEvent(void)
{}

Niski::Input::KeyCodes InputEvent::getKeyCode(void) const
{
	return key_;
}

InputEvent::KeyState InputEvent::getKeyState(void) const
{
	return state_;
}

double InputEvent::getTimeStateChanged(void) const
{
	return stateChanged_;
}