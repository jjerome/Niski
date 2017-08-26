#include "input/MouseListener.h"
#include "input/MouseEvent.h"

#include "gui/RootPanel.h"

namespace Niski
{
	namespace GUI
	{
		class MouseListener : public Niski::Input::MouseListener
		{
		public:
			MouseListener(RootPanel* rootPanel);
			~MouseListener(void);

			mouseEventResponse receiveMouseEvent(const Niski::Input::MouseEvent& event);
			mousePriorityPreference getPriorityPreference(void) const { return mousePriorityPreference::alwaysFirst; }

		private:
			RootPanel* rootPanel_;
		};
	}
}


using namespace Niski::GUI;

MouseListener::MouseListener(RootPanel* rootPanel) : rootPanel_(rootPanel)
{}

MouseListener::~MouseListener(void)
{}