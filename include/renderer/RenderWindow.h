#ifndef __RENDERER_RENDERWINDOW_H__
#define __RENDERER_RENDERWINDOW_H__

#include <string>
#include <stdexcept>
#include <vector>

#include "input/InputSystem.h"
#include "math/Rectangle.h"
#include "utils/win32/Win32Includes.h"

namespace Niski
{
	namespace Renderer
	{

		/*
		===============================================================================
		
			Render window class - automatically handles receiving input (and dispatching
			to the attached input system). 
		
		===============================================================================
		*/
		
		class RenderWindow
		{
		public:
			//
			// Static methods..
			typedef HWND nativeWindowHandle;
			typedef std::vector<RenderWindow*> renderWindowList;
			
			static renderWindowList &	getRenderWindowList(void);
			static void					addRenderWindow(RenderWindow* window);
			static RenderWindow *		getRenderWindow(nativeWindowHandle handle);

		public:
			enum windowStyle
			{
				hasBorder = 0,
				noBorder,
			};

		public:
			RenderWindow(const std::wstring& title, const Niski::Math::Rect2D& dimensions, Niski::Input::InputSystem* inputSystem, RenderWindow::windowStyle winStyle = RenderWindow::hasBorder);
			~RenderWindow(void);

			void						setTitle(const std::wstring& title);
			std::wstring				getTitle(void)									const;

			void						setDimensions(const Niski::Math::Rect2D& dimensions);
			const Niski::Math::Rect2D&	getDimensions(void)								const;

			void						setWindowStyle(RenderWindow::windowStyle winStyle);
			RenderWindow::windowStyle	getWindowStyle(void)							const;

			bool						hasFocus(void)									const;

			bool						getFocus(void);
			bool						activateWindow(void);

			nativeWindowHandle			getNativeHandle(void)							const;

			LRESULT						windowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		private:
			HWND						handle_;
			std::wstring				title_;
			Niski::Math::Rect2D			dimensions_;
			RenderWindow::windowStyle	windowStyle_;
			Niski::Input::InputSystem*  inputSystem_;
			bool						hasFocus_;
			uint32_t					win32Style_;
		};

		//
		// Exceptions..
		class RenderWindowFailedToInitalize : public std::runtime_error
		{
		public:
			RenderWindowFailedToInitalize(const std::string& error) : std::runtime_error(error)
			{}
		};

		class RenderWindowFailedToUpdateWindow : public std::runtime_error
		{
		public:
			RenderWindowFailedToUpdateWindow(const std::string& error) : std::runtime_error(error)
			{}
		};

		//
		// Window Proc
		LRESULT CALLBACK renderWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	}
}

#endif