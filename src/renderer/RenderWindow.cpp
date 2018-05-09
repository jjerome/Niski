#include <sstream>
#include <iostream>
#include "renderer/RenderWindow.h"
#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Renderer;

#if 0

LRESULT CALLBACK Niski::Renderer::renderWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RenderWindow* window = RenderWindow::getRenderWindow(hWnd);

	if(window)
	{
		//
		// TODO: Why are we storing the return of windowProc in result?
		LRESULT result = window->windowProc(uMsg, wParam, lParam);
		return result;
	}
	else
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

//
// Static methods for RenderWindow
RenderWindow::renderWindowList& RenderWindow::getRenderWindowList(void)
{
	static RenderWindow::renderWindowList list;
	return list;
}

void RenderWindow::addRenderWindow(RenderWindow* window)
{
	RenderWindow::renderWindowList& list = getRenderWindowList();

	list.push_back(window);
}

RenderWindow* RenderWindow::getRenderWindow(RenderWindow::nativeWindowHandle handle)
{
	RenderWindow::renderWindowList& list = getRenderWindowList();

	for(auto window : list)
	{
		if(window->getNativeHandle() == handle)
		{
			return window;
		}
	}

	return nullptr;
}
#endif

RenderWindow::RenderWindow(const std::string& title, const Niski::Math::Rect2D& dimensions, Niski::Input::InputSystem* inputSystem, windowStyle winStyle /* = RenderWindow::hasBorder */) 
	: title_(title), 
	dimensions_(dimensions), 
	window_(nullptr), 
	windowStyle_(winStyle), 
	inputSystem_(inputSystem), 
	hasFocus_(true)
{
	uint32_t flags = (winStyle == RenderWindow::hasBorder) ? SDL_WINDOW_INPUT_GRABBED : SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED;

	window_ = SDL_CreateWindow(title.c_str(), dimensions.left, dimensions.top, dimensions.right, dimensions.bottom, flags);

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

std::string RenderWindow::getTitle(void) const
{
	return title_;
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

const Niski::Math::Rect2D& RenderWindow::getDimensions(void) const
{
	return dimensions_;
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

RenderWindow::windowStyle RenderWindow::getWindowStyle(void) const
{
	return windowStyle_;
}

bool RenderWindow::hasFocus(void) const
{
	return hasFocus_;
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

SDL_Window* RenderWindow::getWndHandle(void) const
{
	return window_;
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

#if 0
LRESULT RenderWindow::windowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{		
	case WM_SETFOCUS:
		hasFocus_ = true;
		return 0;

	case WM_KILLFOCUS:
		hasFocus_ = false;
		return 0;

	case WM_ACTIVATE:
		if(LOWORD(wParam) == WA_ACTIVE)
		{
			//
			// Our window is now active
		}
		else
		{
			//
			// Our window is now inactive
			// TODO: Ideally we should stop rendering altogether, I think. 
		}

		return DefWindowProc(getNativeHandle(), uMsg, wParam, lParam);

	case WM_DESTROY:
		//
		// TODO: We should end our game logic, etc. 
		Niski::Utils::bitch("Our window was destroyed.");
		return 0;

	case WM_UNICHAR:
		//
		// This is specifically for WM_UNICHAR
		// just to indicate we understand the msg
		if (wParam == UNICODE_NOCHAR)
		{
			return TRUE;
		}
		//
		// Otherwise bleed through to the input manager like normal. 

	case WM_MOUSEWHEEL:
	case WM_MOUSEMOVE:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_CHAR:
		//
		// Dispatch to our attached input system. 
		//
		// TODO: Allow system commands to pass through, right?
		if(inputSystem_)
		{
			inputSystem_->run(uMsg, wParam, lParam);
		}
		return 0;

	default:
		return DefWindowProc(getNativeHandle(), uMsg, wParam, lParam);
	}
}
#endif