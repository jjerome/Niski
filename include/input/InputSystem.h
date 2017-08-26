#ifndef __INPUT_INPUTSYSTEM_H__
#define __INPUT_INPUTSYSTEM_H__

#include "engine/KeyBindings.h"
#include "input/CharListener.h"
#include "input/InputListener.h"
#include "input/MouseListener.h"
#include "input/Win32Translator.h"
#include "math/Vec2d.h"

#include <vector>

namespace Niski
{
	namespace Input
	{
		class InputSystem
		{
		public:
			InputSystem(void);
			~InputSystem(void);

			void	addInputListener(InputListener* listener);
			bool	removeInputListener(InputListener* listener);
			void	dispatchInputEvent(const InputEvent& event) const;

			void	addMouseListener(MouseListener* listener);
			bool	removeMouseListener(MouseListener* listener);
			void	dispatchMouseEvent(const MouseEvent& event) const;
			
			//
			// TODO: Should this allow for multiple listeners? Seems
			// pointless outside of the GUI engine tbh. 
			void	setCharListener(CharListener* listener);
			void	dispatchChar(wchar_t ch);

			/* TODO: Make it clear this is a windows only function */
			void	run(UINT uMsg, WPARAM wParam, LPARAM lParam);

		private:
			void	handleMouseEvent(WPARAM wParam, bool pressed);

			std::vector<InputListener*>		inputListeners_;
			std::vector<MouseListener*>		mouseListeners_;
			CharListener*					charListener_;
			Niski::Input::Win32Translator*	translator_;
			Niski::Math::Vector2D<int32_t>	lastMousePos_;
		};
	}
}

#endif