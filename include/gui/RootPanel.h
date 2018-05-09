#ifndef __GUI_ROOTPANEL_H__
#define __GUI_ROOTPANEL_H__

#include "gui/Base.h"
#include "input/MouseEvent.h"
#include "input/InputEvent.h"
#include "input/CharListener.h"

namespace Niski
{
	namespace GUI
	{
		class RootPanel : public Base, public Niski::Input::InputListener, public Niski::Input::MouseListener, public Niski::Input::CharListener
		{
		public:
			RootPanel(void);
			~RootPanel(void);

			bool isActive(void) const { return isActive_; }
			void setActive(bool active) { isActive_ = active; }

			//
			// Mouse Event stuff
			mouseEventResponse receiveMouseEvent(const Niski::Input::MouseEvent& event);
			mousePriorityPreference getMousePriorityPreference(void) const { return mousePriorityPreference::alwaysFirst; }

			inputEventResponse receiveMouseButtonEvent(const Niski::Input::MouseBtnEvent& event);

			//
			// Keyboard Event stuff
			inputEventResponse receiveInputEvent(const Niski::Input::InputEvent& inputEvent);
			inputPriorityPreference getInputPriorityPreference(void) const { return inputPriorityPreference::alwaysFirst; }

			//
			// Char listener stuff
			void receiveChar(wchar_t ch);

		private:
			Base* activeControl_;
			bool isActive_;
			Niski::Math::Vector2D<int32_t> mousePosition_;
		};
	}
}

#endif