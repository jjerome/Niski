#include "input/InputSystem.h"
#include "input/MouseEvent.h"
#include "utils/Log.h"
#include "utils/win32/Win32Includes.h"

#include <algorithm>

using namespace Niski::Input;

InputSystem::InputSystem(void) : lastMousePos_(0, 0), charListener_(nullptr)
{
	translator_ = new Win32Translator();
}

InputSystem::~InputSystem(void)
{}

void InputSystem::addInputListener(InputListener* listener)
{
	inputListeners_.push_back(listener);

	std::sort(inputListeners_.begin(), inputListeners_.end(), [](const InputListener* a, const InputListener* b) {
		if(a->getInputPriorityPreference() < b->getInputPriorityPreference())
		{
			return true;
		}

		return false;
	});
}

bool InputSystem::removeInputListener(InputListener* listener)
{
	for(auto it = inputListeners_.begin(); it != inputListeners_.end(); ++it)
	{
		if((*it) == listener)
		{
			inputListeners_.erase(it);

			return true;
		}
	}

	return false;
}

void InputSystem::dispatchInputEvent(const InputEvent& event) const
{
	if(inputListeners_.size() > 0)
	{
		for(auto listener : inputListeners_)
		{
			//
			// Iterate through all of our listeners (should
			// already be sorted automatically)
			// and pass the event along if the listener doesn't
			// acknowledge the event. 
			if(listener->receiveInputEvent(event) == InputListener::inputEventResponse::acknowledged)
			{
				break;
			}
		}
	}
}

//
// Hate that this function is just duplicating code from
// InputSystem::addInputListener, but alas..
void InputSystem::addMouseListener(MouseListener* listener)
{
	mouseListeners_.push_back(listener);

	std::sort(mouseListeners_.begin(), mouseListeners_.end(), [](const MouseListener* a, const MouseListener* b) {
		if(a->getMousePriorityPreference() < b->getMousePriorityPreference())
		{
			return true;
		}

		return false;
	});
}

bool InputSystem::removeMouseListener(MouseListener* listener)
{
	for(auto it = mouseListeners_.begin(); it != mouseListeners_.end(); ++it)
	{
		if(*it == listener)
		{
			mouseListeners_.erase(it);

			return true;
		}
	}

	return false;
}

void InputSystem::dispatchMouseEvent(const MouseEvent& event) const
{
	if(mouseListeners_.size() > 0)
	{
		for(auto listener : mouseListeners_)
		{
			//
			// Iterate through all of our listeners (should
			// already be sorted automatically)
			// and pass the event along if the listener doesn't
			// acknowledge the event. 
			if(listener->receiveMouseEvent(event) == MouseListener::mouseEventResponse::acknowledged)
			{
				break;
			}
		}
	}
}

void InputSystem::setCharListener(CharListener* charListener)
{
	charListener_ = charListener;
}

void InputSystem::dispatchChar(wchar_t ch)
{
	if (charListener_ != nullptr)
	{
		charListener_->receiveChar(ch);
	}
}

void InputSystem::run(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//
	// NOTE: If you're adding new messages to watch here
	// make sure RenderWindow knows to dispatch those events to the input system!
	switch(uMsg)
	{
	case WM_MOUSEWHEEL:
		{
			//
			// TODO: Should we be dispatching this to the input system, or to the mouse listener?
			int32_t zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

			if(zDelta < 0)
			{
				// Scrolled down
			}
			else
			{
				// Scrolled up..
			}
		}
		break;

	case WM_MOUSEMOVE:
		{
			//
			// Calculate the difference since the last
			// update..
			Niski::Math::Vector2D<int32_t> currentMousePos(0, 0);
			currentMousePos.x = GET_X_LPARAM(lParam);
			currentMousePos.y = GET_Y_LPARAM(lParam);

			auto difference = currentMousePos - lastMousePos_;

			MouseEvent event(difference);
			dispatchMouseEvent(event);

			lastMousePos_ = currentMousePos;
		}
		break;

	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_XBUTTONDOWN:
		{
			//wParam = GET_KEYSTATE_WPARAM(wParam);
			//
			// TODO: wParam is bit set to determine; our translator 
			// doesn't handle this. We should spawn multple events 
			// in response? 
			// TODO: This is also an issue for xUP mouse commands as well. 
			handleMouseEvent(wParam, true);
		}
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			KeyCodes key = translator_->translate(wParam);
			InputEvent event(key, InputEvent::Pressed, 0);
			dispatchInputEvent(event);
		}
		break;

	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
		{
			handleMouseEvent(wParam, false);
		}
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		{
			KeyCodes key = translator_->translate(wParam);
			InputEvent event(key, InputEvent::Released, 0);
			dispatchInputEvent(event);
		}
		break;

	case WM_UNICHAR:
	case WM_CHAR:
		{
			//
			// TODO: Dispatch to the GUI _only_
			// as everything else doesn't care 
			// about localized keys/etc. 
			switch (wParam)
			{
				//
				// Because we're already parsing the actual keys sent through WM_KEYUP, etc.
				// We don't need to care about the control characters sent here. 
			case 0x08:
			case 0x0A:
			case 0x1B:
			case 0x09:
			case 0x0D:
				break;
			default:
				dispatchChar(wchar_t(wParam));
				break;
			}
		}
		break;

	default:
		break;
	}
}

void /* Private */ InputSystem::handleMouseEvent(WPARAM wParam, bool pressed)
{
	Niski::Input::InputEvent::KeyState state = (pressed) ? InputEvent::Pressed : InputEvent::Released;

	if (wParam & MK_LBUTTON)
	{
		dispatchInputEvent(InputEvent(KeyCodes::Mouse_LeftButton, state, 0));
	}

	if (wParam & MK_RBUTTON)
	{
		dispatchInputEvent(InputEvent(KeyCodes::Mouse_RightButton, state, 0));
	}

	if (wParam & MK_MBUTTON)
	{
		dispatchInputEvent(InputEvent(KeyCodes::Mouse_MiddleButton, state, 0));
	}

	if (wParam & MK_XBUTTON1)
	{
		dispatchInputEvent(InputEvent(KeyCodes::Mouse_Side_Backward, state, 0));
	}

	if (wParam & MK_XBUTTON2)
	{
		dispatchInputEvent(InputEvent(KeyCodes::Mouse_Side_Forward, state, 0));
	}
}