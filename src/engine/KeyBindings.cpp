#include "engine/KeyBindings.h"
#include "engine/ConCommand.h"
#include "input/KeyCodeToString.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"

using namespace Niski::Engine;

//
// Function definition for BindCmd
void BindCmd::run(const std::vector<std::string>& args)
{
	if(keyBinds_ && args.size() > 1)
	{
		Niski::Input::KeyCodes kc = Niski::Input::StringToKeyCode(args[0]);

		if (kc != Niski::Input::KeyCodes::Key_InvalidKey)
		{
			//
			// Doesn't matter if the command is BS. 
			keyBinds_->setBinding(kc, args[1]);
		}
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
		std::string bind = getBinding(event.getButton());

		//
		// TODO: Temporary?
		if (bind == "INVALID_KEY")
		{
			return pass;
		}

		std::vector<std::string> args;
		Niski::Utils::String::parse(bind, args);

		ConCommand* cmd = ConCommand::getCommand(args[0]);

		if (cmd)
		{
			//
			// Blugh kinda terrible. 
			args.erase(args.begin());
			cmd->run(args);

			return acknowledged;
		}
	}

	if (event.getState() == Niski::Input::KeyState::Released)
	{
		std::string bind = getBinding(event.getButton());

		//
		// TODO: Temporary?
		if (bind == "INVALID_KEY")
		{
			return pass;
		}

		std::vector<std::string> args;
		Niski::Utils::String::parse(bind, args);

		std::string commandText = args[0];

		//
		// If the command begins with +
		// then run the - version of the command. 
		// Note that commands run when the button is pressed so we ONLY
		// care if the command is an active one.
		if (commandText[0] == '+')
		{
			commandText[0] = '-';

			ConCommand* releaseCmd = ConCommand::getCommand(commandText);

			if (releaseCmd)
			{
				//
				// Blugh kinda terrible. 
				args.erase(args.begin());
				releaseCmd->run(args);

				return acknowledged;
			}
		}
	}

	return pass;
}

Niski::Input::InputListener::inputEventResponse KeyBindings::receiveInputEvent(const Niski::Input::InputEvent& inputEvent)
{
	if(inputEvent.getKeyState() == Niski::Input::KeyState::Pressed)
	{
		std::string bind = getBinding(inputEvent.getKeyCode());

		//
		// TODO: Temporary?
		if (bind == "INVALID_KEY")
		{
			return pass;
		}

		std::vector<std::string> args;
		Niski::Utils::String::parse(bind, args);

		ConCommand* cmd = ConCommand::getCommand(args[0]);

		if (cmd)
		{
			//
			// Blugh kinda terrible. 
			args.erase(args.begin());
			cmd->run(args);

			return acknowledged;
		}
	}

	if(inputEvent.getKeyState() == Niski::Input::KeyState::Released)
	{
		std::string bind = getBinding(inputEvent.getKeyCode());
		
		//
		// TODO: Temporary?
		if (bind == "INVALID_KEY")
		{
			return pass;
		}

		std::vector<std::string> args;
		Niski::Utils::String::parse(bind, args);

		std::string commandText = args[0];

		//
		// If the command begins with +
		// then run the - version of the command. 
		if (commandText[0] == '+')
		{
			commandText[0] = '-';

			ConCommand* releaseCmd = ConCommand::getCommand(commandText);

			if (releaseCmd)
			{
				//
				// Blugh kinda terrible. 
				args.erase(args.begin());
				releaseCmd->run(args);

				return acknowledged;
			}
		}
	}

	return pass;
}