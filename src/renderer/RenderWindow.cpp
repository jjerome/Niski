#include <sstream>
#include <iostream>
#include "renderer/RenderWindow.h"
#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Renderer;

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

RenderWindow::RenderWindow(const std::wstring& title, const Niski::Math::Rect2D& dimensions, Niski::Input::InputSystem* inputSystem, windowStyle winStyle /* = RenderWindow::hasBorder */) 
	: title_(title), 
	dimensions_(dimensions), 
	handle_(nullptr), 
	windowStyle_(winStyle), 
	inputSystem_(inputSystem), 
	hasFocus_(true), 
	win32Style_(0)
{
	//
	// Add ourselves to the render window list for the winproc
	addRenderWindow(this);

	WNDCLASS windowClass;
	::ZeroMemory(&windowClass, sizeof(windowClass));

	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC) renderWindowProc;
	windowClass.hInstance = ::GetModuleHandle(nullptr);
	windowClass.lpszClassName = L"NiskiEngineWindow";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);

	ATOM registeredClass = ::RegisterClass(&windowClass);
	Niski::Utils::Assert(registeredClass != 0, "Failed to register Window Class", __FILE__, __FUNCSIG__, __LINE__);

	win32Style_ = (windowStyle_ == noBorder) ? WS_POPUP : WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME & ~WS_MAXIMIZEBOX);
	RECT windowRect = dimensions_.toWin32Rect();
	windowRect.top = 0; 
	windowRect.left = 0;
	BOOL result = ::AdjustWindowRect(&windowRect, win32Style_, FALSE);

	if(result == FALSE)
	{
		std::ostringstream error("Failed to get adjusted window rectangle. \n\nWindows API returned error code: ");
		error << ::GetLastError();
		throw RenderWindowFailedToInitalize(error.str());
	}

	handle_ = ::CreateWindow(L"NiskiEngineWindow",
		title_.c_str(),
		win32Style_,
		dimensions_.left, 
		dimensions_.top, 
		windowRect.right - windowRect.left, 
		windowRect.bottom - windowRect.top, 
		nullptr,
		nullptr,
		::GetModuleHandle(nullptr),
		nullptr);

	if(handle_ == nullptr)
	{
		std::ostringstream error("Failed to create window. \n\nWindows API returned error code: ");
		error << ::GetLastError();
		throw RenderWindowFailedToInitalize(error.str());
	}

	::ShowWindow(handle_, SW_SHOWNORMAL);
	::SetFocus(handle_);
}

RenderWindow::~RenderWindow(void)
{
	if(handle_ != nullptr)
	{
		::CloseWindow(handle_);
	}
}

void RenderWindow::setTitle(const std::wstring& title)
{
	Niski::Utils::Assert(handle_ != INVALID_HANDLE_VALUE, "Invalid handle - cannot set title.", __FILE__, __FUNCSIG__, __LINE__);
	
	BOOL result = ::SetWindowText(handle_, title.c_str());

	if(result == FALSE)
	{
		std::ostringstream error("Failed to set window title. \n\nWindows API returned error code: ");
		error << GetLastError();
		throw RenderWindowFailedToUpdateWindow(error.str());
	}

	title_ = title;
}

std::wstring RenderWindow::getTitle(void) const
{
	return title_;
}

void RenderWindow::setDimensions(const Niski::Math::Rect2D& dimensions)
{
	if(dimensions_ == dimensions)
	{
		//
		// Nothing to do - we're already that size/position anyways
		Niski::Utils::bitch("Attempted to set our dimensions for our render window to the dimensions we already have!");

		return;
	}

	RECT windowRect = dimensions.toWin32Rect();
	windowRect.top = 0; 
	windowRect.left = 0;
	BOOL result = ::AdjustWindowRect(&windowRect, 
		win32Style_, 
		FALSE);

	if(result == FALSE)
	{
		std::ostringstream error("Failed to get adjusted window rectangle. \n\nWindows API returned error code: ");
		error << GetLastError();
		throw RenderWindowFailedToInitalize(error.str());
	}

	result = ::SetWindowPos(handle_, 
		nullptr, 
		dimensions_.left, 
		dimensions_.top, 
		windowRect.right - windowRect.left, 
		windowRect.bottom - windowRect.top, 
		SWP_SHOWWINDOW);

	if(result == FALSE)
	{
		std::ostringstream error("Failed to set window position. \n\nWindows API returned error code: ");
		error << GetLastError();
		throw RenderWindowFailedToUpdateWindow(error.str());
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
	win32Style_ = (windowStyle_ == noBorder) ? WS_POPUP : WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME & ~WS_MAXIMIZEBOX);
	BOOL result = ::SetWindowLongPtr(handle_, GWL_STYLE, win32Style_);

	if(result == FALSE)
	{
		std::ostringstream error("Failed to new window style for ");
		error << ((windowStyle_ == hasBorder) ? "borderless" : "bordered") << " mode. \n\nWindows API returned error code: " << GetLastError();
		throw RenderWindowFailedToUpdateWindow(error.str());
	}

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
	if(hasFocus_)
	{
		Niski::Utils::bitch("Attempted to acquire focus on our window, but we already have focus!");

		return true;
	}

	hasFocus_ = ::SetFocus(handle_) != nullptr;

	return hasFocus_;
}

bool RenderWindow::activateWindow(void)
{
	return ::SetForegroundWindow(handle_) != FALSE;
}

HWND RenderWindow::getNativeHandle(void) const
{
	return handle_;
}

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