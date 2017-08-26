#ifndef __INPUT_INPUTLISTENER_H__
#define __INPUT_INPUTLISTENER_H__

#include "input/InputEvent.h"

namespace Niski
{
	namespace Input
	{
		class InputListener
		{
		public:
			enum inputEventResponse
			{
				//
				// acknowledged and the input even does not need
				// to be passed to another listener. 
				acknowledged = 0,

				//
				// the event should be passed to the next listener. 
				pass,
			};

			enum inputPriorityPreference
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
			InputListener(void) {}

			virtual inputEventResponse receiveInputEvent(const InputEvent& inputEvent) = 0;
			virtual inputPriorityPreference getInputPriorityPreference(void) const { return dontCare; }
		};
	}
}

#endif