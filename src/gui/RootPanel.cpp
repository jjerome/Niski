#include "gui/RootPanel.h"

#include <iostream>

using namespace Niski::GUI;

RootPanel::RootPanel(void) : Base(nullptr, "RootPanel"), mousePosition_(0, 0), isActive_(true)
{}

RootPanel::~RootPanel(void)
{}

Niski::Input::MouseListener::mouseEventResponse RootPanel::receiveMouseEvent(const Niski::Input::MouseEvent& event)
{
	if(!isActive())
	{
		return MouseListener::pass;
	}
	
	mousePosition_ += event.getPositionDifference();

	//
	// TODO: The control that is being hovered over (for effects, etc) should be updated.

	return MouseListener::acknowledged;
}

Niski::Input::InputListener::inputEventResponse RootPanel::receiveInputEvent(const Niski::Input::InputEvent& inputEvent)
{
	if(!isActive())
	{
		return InputListener::pass;
	}

	//
	//
	// check if we have a new active control. 
	if(inputEvent.getKeyCode() == Niski::Input::Mouse_LeftButton)
	{
		std::cout << "Attempting to set a new activeControl_ . . . ";

		auto child = getChildAtPosition(mousePosition_);

		if(child != nullptr)
		{
			std::cout << "Succeeded" << std::endl;
			activeControl_ = child;
		}
		else
		{
			std::cout << "Failed" << std::endl;
			activeControl_ = nullptr;

			return InputListener::pass;
		}
	}

	if(activeControl_)
	{
		//
		// TODO: send activeControl_ the input event.
		activeControl_->receiveKeyboardInput(inputEvent);
	}
	else
	{
		return InputListener::pass;
	}

	return InputListener::acknowledged;
}

void RootPanel::receiveChar(wchar_t ch)
{
	//
	// TODO: Probably should figure some stuff out here, eventually. 
	if (activeControl_)
	{
		activeControl_->receiveChar(ch);
	}
}