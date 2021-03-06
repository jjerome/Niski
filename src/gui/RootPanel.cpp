#include "gui/RootPanel.h"

#include <iostream>
#include <sstream>

using namespace Niski::GUI;

RootPanel::RootPanel(void) : Base(nullptr, "RootPanel"), mousePosition_(0, 0), isActive_(true)
{
	mousePositionLbl_ = new Label(this, "MousePositionLabel", Niski::Math::Vector2D<int32_t>(1100, 680), Niski::GUI::FontCfg("Consolas", 8));
	mousePositionLbl_->setSize(Niski::Math::Vector2D<int32_t>(400, 50));
}

RootPanel::~RootPanel(void)
{}

Niski::Input::MouseListener::mouseEventResponse RootPanel::receiveMouseEvent(const Niski::Input::MouseEvent& event)
{
	if(!isActive())
	{
		return MouseListener::pass;
	}

	std::ostringstream ctrlStr;

	if (!activeControl_)
	{
		ctrlStr << "Current Control: null";
	}
	else
	{
		ctrlStr << "Current Control: " << activeControl_->getName();
	}
	
	mousePosition_ = event.getPosition();

	std::ostringstream woss;
	woss << "Mouse Pos: " << mousePosition_.x << ", " << mousePosition_.y << "\n"
		<< ctrlStr.str();

	mousePositionLbl_->setText(woss.str());

	//
	// TODO: The control that is being hovered over (for effects, etc) should be updated.

	return MouseListener::acknowledged;
}

Niski::Input::InputListener::inputEventResponse RootPanel::receiveMouseButtonEvent(const Niski::Input::MouseBtnEvent& event)
{
	if (!isActive())
	{
		return InputListener::pass;
	}

	//
	//
	// check if we have a new active control. 
	if (event.getButton() == Niski::Input::KeyCodes::Mouse_LeftButton && event.getState() == Niski::Input::KeyState::Pressed)
	{
		auto child = getChildAtPosition(mousePosition_);

		if (child != nullptr)
		{
			std::cout << "Found child [" << child->getName() << "] at position (" << mousePosition_.x << "," << mousePosition_.y << ")" << std::endl;
			activeControl_ = child;

			return InputListener::acknowledged;
		}
		else
		{
			std::cout << "Unable to find a GUI child at position (" << mousePosition_.x << "," << mousePosition_.y << ")" << std::endl;
			activeControl_ = nullptr;
		}
	}

	return InputListener::pass;
}

Niski::Input::InputListener::inputEventResponse RootPanel::receiveInputEvent(const Niski::Input::InputEvent& inputEvent)
{
	if (!isActive())
	{
		return InputListener::pass;
	}


	if(activeControl_)
	{
		//
		// TODO: send activeControl_ the input event.
		activeControl_->receiveKeyboardInput(inputEvent);

		return InputListener::acknowledged;
	}

	return InputListener::pass;

	
}

void RootPanel::receiveTextInput(std::string str)
{
	//
	// TODO: Probably should figure some stuff out here, eventually. 
	if (activeControl_)
	{
		activeControl_->receiveTextInput(str);
	}
}