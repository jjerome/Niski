#include <sstream>
#include <iostream>
#include "renderer/RenderWindow.h"
#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Renderer;

RenderWindow::RenderWindow(const std::string& title, const Niski::Math::Rect2D& dimensions, Niski::Input::InputSystem* inputSystem, windowStyle winStyle /* = RenderWindow::hasBorder */) 
	: title_(title), 
	dimensions_(dimensions), 
	window_(nullptr), 
	windowStyle_(winStyle), 
	inputSystem_(inputSystem), 
	hasFocus_(true),
	hasClosed_(false)
{
	uint32_t flags = (winStyle == RenderWindow::hasBorder) ? 0 : SDL_WINDOW_BORDERLESS;

	window_ = SDL_CreateWindow(title.c_str(), dimensions.left, dimensions.top, dimensions.right, dimensions.bottom, flags);

	if (window_ == nullptr)
	{
		std::ostringstream oss;
		oss << "SDL failed to create a window. SDL returned" << SDL_GetError();

		throw RenderWindowFailedToInitalize(oss.str());
	}

	SDL_RaiseWindow(window_);
}

RenderWindow::~RenderWindow(void)
{
	if(window_ != nullptr)
	{
		SDL_DestroyWindow(window_);
	}
}

void RenderWindow::setTitle(const std::string& title)
{
	Niski::Utils::Assert(window_ != nullptr, "Invalid handle - cannot set title.", __FILE__, __FUNCSIG__, __LINE__);

	SDL_SetWindowTitle(window_, title.c_str());

	title_ = title;
}

void RenderWindow::setDimensions(const Niski::Math::Rect2D& dimensions)
{
	Niski::Utils::Assert(window_ != nullptr, "Invalid handle - cannot set dimensions.", __FILE__, __FUNCSIG__, __LINE__);

	if(dimensions_ == dimensions)
	{
		//
		// Nothing to do - we're already that size/position anyways
		Niski::Utils::bitch("Attempted to set our dimensions for our render window to the dimensions we already have!");

		return;
	}

	if (dimensions_.top != dimensions.top || dimensions_.left == dimensions.left)
	{
		SDL_SetWindowPosition(window_, dimensions.left, dimensions.top);
		
	}
	
	if (dimensions_.bottom != dimensions.bottom || dimensions_.right != dimensions.right)
	{
		SDL_SetWindowSize(window_, dimensions.right, dimensions.bottom);
	}

	//
	// Set the dimensions only after it's been adjusted. 
	dimensions_ = dimensions;
}

void RenderWindow::setWindowStyle(RenderWindow::windowStyle winStyle)
{
	Niski::Utils::Assert(window_ != nullptr, "Invalid handle - cannot set window style.", __FILE__, __FUNCSIG__, __LINE__);

	SDL_bool bordered = (windowStyle_ == noBorder) ? SDL_FALSE : SDL_TRUE;

	SDL_SetWindowBordered(window_, bordered);
	

	//
	// Set the window style after it's officially done
	windowStyle_ = winStyle;

	//
	// Update our dimensions again (since it's adjusted for the window style)
	setDimensions(dimensions_);
}

bool RenderWindow::getFocus(void)
{
	Niski::Utils::Assert(window_ != nullptr, "Invalid handle - cannot grab focus.", __FILE__, __FUNCSIG__, __LINE__);

	if(hasFocus_)
	{
		Niski::Utils::bitch("Attempted to acquire focus on our window, but we already have focus!");

		return true;
	}

	SDL_SetWindowGrab(window_, SDL_TRUE);

	return hasFocus_;
}

void RenderWindow::activateWindow(void)
{
	Niski::Utils::Assert(window_ != nullptr, "Invalid handle - cannot activate window.", __FILE__, __FUNCSIG__, __LINE__);

	SDL_SetWindowGrab(window_, SDL_TRUE);
}

void RenderWindow::handleWindowEvents(const SDL_Event& evt)
{
	switch (evt.window.event)
	{
	case SDL_WINDOWEVENT_FOCUS_LOST:
		hasFocus_ = false;
		break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
		hasFocus_ = true;
		break;

	case SDL_WINDOWEVENT_CLOSE: 
		//
		// TODO: 
		hasClosed_ = true;
		break;

	case SDL_WINDOWEVENT_MOVED:
		dimensions_.left = evt.window.data1;
		dimensions_.top = evt.window.data2;
		break;

	case SDL_WINDOWEVENT_RESIZED:
		dimensions_.right = evt.window.data1;
		dimensions_.bottom = evt.window.data2;
		break;

	default:
		break;
	}
}

void RenderWindow::pollEvents(void)
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_WINDOWEVENT:
			handleWindowEvents(evt);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_TEXTINPUT:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
		case SDL_MOUSEMOTION:
			if (inputSystem_)
			{
				inputSystem_->receiveSDLEvent(evt);
			}
			break;

		default:
			break;
		}
	}
}