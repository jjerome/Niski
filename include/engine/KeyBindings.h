#ifndef __ENGINE_KEYBINDINGS_H__
#define __ENGINE_KEYBINDINGS_H__

#include "engine/ConCommand.h"
#include "input/KeyCodes.h"
#include "input/InputEvent.h"
#include "input/InputListener.h"

#include <string>
#include <map>

namespace Niski
{
	namespace Engine
	{
		//
		// Forward declaration for the BindCmd
		class KeyBindings;

		/*
		===============================================================================
		
			A simple bind command - it automatically adds a binding to a key you 
			specify. Syntax: bind <key> <command>
		
		===============================================================================
		*/

		class BindCmd : public Niski::Engine::ConCommand
		{
		public:
			BindCmd(KeyBindings* keyBinds) : Niski::Engine::ConCommand("Engine::Bind"), keyBinds_(keyBinds)
			{}

			void run(void);

		private:
			KeyBindings* keyBinds_;
		};

		/*
		===============================================================================
		
			Key binding system. Receives input events from the input system
			it is attached to and then checks its list of stored key/bind combos
			and handles execution of the command. 
		
		===============================================================================
		*/

		class KeyBindings : public Niski::Input::InputListener
		{
		public:
			KeyBindings(void);
			~KeyBindings(void);

			void							setBinding(Niski::Input::KeyCodes key, std::string command);
			const	std::string 			getBinding(Niski::Input::KeyCodes key);

			virtual inputEventResponse			receiveInputEvent(const Niski::Input::InputEvent& inputEvent);

					inputPriorityPreference		getInputPriorityPreference(void) const { return InputListener::alwaysLast; }

		private:
			std::map<Niski::Input::KeyCodes, std::string> keyBinds;
			BindCmd bindCmd_;
		};
	}
}
#endif