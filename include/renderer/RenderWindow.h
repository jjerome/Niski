#ifndef __RENDERER_RENDERWINDOW_H__
#define __RENDERER_RENDERWINDOW_H__

#include <string>
#include <stdexcept>
#include <vector>

#include "SDL/SDL.h"

#include "input/InputSystem.h"
#include "math/Rectangle.h"

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
			enum windowStyle
			{
				hasBorder = 0,
				noBorder,
			};

		public:
			RenderWindow(const std::string& title, const Niski::Math::Rect2D& dimensions, Niski::Input::InputSystem* inputSystem, RenderWindow::windowStyle winStyle = RenderWindow::hasBorder);
			~RenderWindow(void);

			void						setTitle(const std::string& title);
			std::string					getTitle(void)									const { return title_;  }

			void						setDimensions(const Niski::Math::Rect2D& dimensions);
			const Niski::Math::Rect2D&	getDimensions(void)								const { return dimensions_;  }

			void						setWindowStyle(RenderWindow::windowStyle winStyle);
			RenderWindow::windowStyle	getWindowStyle(void)							const { return windowStyle_;  }

			bool						hasFocus(void)									const { return hasFocus_;  }

			bool						isClosed(void)									const { return hasClosed_;  }

			bool						getFocus(void);
			void						activateWindow(void);

			SDL_Window*					getWndHandle(void)							const { return window_;  }

			void						handleWindowEvents(const SDL_Event& evt);

			void						pollEvents(void);

		private:
			SDL_Window*					window_;
			std::string					title_;
			Niski::Math::Rect2D			dimensions_;
			RenderWindow::windowStyle	windowStyle_;
			Niski::Input::InputSystem*  inputSystem_;
			bool						hasFocus_;
			bool						hasClosed_;
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
	}
}

#endif