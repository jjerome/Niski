#include "engine/KeyBindings.h"
#include "engine/ConCommand.h"
#include "input/KeyCodeToString.h"
#include "utils/Log.h"

using namespace Niski::Engine;

//
// Function definition for BindCmd
void BindCmd::run(void)
{
	if(keyBinds_)
	{
		keyBinds_->setBinding(Niski::Input::Key_InvalidKey, "TODO");
	}
}

KeyBindings::KeyBindings(void) : bindCmd_(this)
{}

KeyBindings::~KeyBindings(void)
{}

void KeyBindings::setBinding(Niski::Input::KeyCodes key, std::string command)
{
	//
	// Remove any previous binds.
	auto it = keyBinds.find(key);

	if(it != keyBinds.end())
	{
		keyBinds.erase(it);
	}

	keyBinds.insert(std::pair<Niski::Input::KeyCodes, std::string>(key, command));
}

const std::string KeyBindings::getBinding(Niski::Input::KeyCodes key)
{
	auto it = keyBinds.find(key);

	if(it != keyBinds.end())
	{
		return it->second;
	}
	else
	{
		//
		// TODO: Throw exception?

		//
		// Log it
		{
			std::ostringstream err;
			err << "Failed to obtain binding for key <" << Niski::Input::KeyCodeToString(key) << ">";
			Niski::Utils::bitch(err.str());
		}

		return "INVALID_KEY";
	}
}

Niski::Input::InputListener::inputEventResponse KeyBindings::receiveMouseButtonEvent(const Niski::Input::MouseBtnEvent& event)
{

	if (event.getState() == Niski::Input::KeyState::Pressed)
	{
		std::string command = getBinding(event.getButton());

		//
		// TODO: Temporary?
		if (command == "INVALID_KEY")
		{
			return pass;
		}

		ConCommand* cmd = ConCommand::getCommand(command);

		if (cmd)
		{
			cmd->run();
		}
		else
		{
			return pass;
		}
	}

	if (event.getState() == Niski::Input::KeyState::Released)
	{
		std::string command = getBinding(event.getButton());

		//
		// TODO: Temporary?
		if (command == "INVALID_KEY")
		{
			return pass;
		}

		//
		// If the command begins with +
		// then run the - version of the command. 
		if (command[0] == '+')
		{
			command[0] = '-';

			ConCommand* cmd = ConCommand::getCommand(command);

			if (cmd)
			{
				cmd->run();
			}
		}
	}

	return acknowledged;
}

Niski::Input::InputListener::inputEventResponse KeyBindings::receiveInputEvent(const Niski::Input::InputEvent& inputEvent)
{
	if(inputEvent.getKeyState() == Niski::Input::KeyState::Pressed)
	{
		std::string command = getBinding(inputEvent.getKeyCode());

		//
		// TODO: Temporary?
		if(command == "INVALID_KEY")
		{
			return pass;
		}

		ConCommand* cmd = ConCommand::getCommand(command);

		if(cmd)
		{
			cmd->run();
		}
		else
		{
			return pass;
		}
	}

	if(inputEvent.getKeyState() == Niski::Input::KeyState::Released)
	{
		std::string command = getBinding(inputEvent.getKeyCode());
		
		//
		// If the command begins with +
		// then run the - version of the command. 
		if(command[0] == '+')
		{
			command[0] = '-';

			ConCommand* cmd = ConCommand::getCommand(command);

			if(cmd)
			{
				cmd->run();
			}
		}
	}

	return acknowledged;
}