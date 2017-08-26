#ifndef __INPUT_MOUSELISTENER_H__
#define __INPUT_MOUSELISTENER_H__

#include "input/MouseEvent.h"

namespace Niski
{
	namespace Input
	{
		class MouseListener
		{
		public:
			enum mouseEventResponse
			{
				//
				// acknowledged and the input even does not need
				// to be passed to another listener. 
				acknowledged = 0,

				//
				// the event should be passed to the next listener. 
				pass,
			};

			enum mousePriorityPreference
			{
				//
				// There can only be ONE of both always priorities.
				// alwaysFirst (taken by GUI)
				alwaysFirst = 0,

				//
				// Prefer being as close to first as possible
				preferFirst,

				//
				// Typically in the middle between preferFirst and preferLast
				dontCare,

				//
				// Prefer being as close to last as possible
				preferLast,

				//
				// alwaysLast (taken by Engine)
				alwaysLast
			};

		public:
			MouseListener(void) {}

			virtual mouseEventResponse receiveMouseEvent(const MouseEvent& event) = 0;
			virtual mousePriorityPreference getMousePriorityPreference(void) const { return mousePriorityPreference::dontCare; }
		};
	}
}

#endif