#ifndef __GUI_TEXTINPUT_H__
#define __GUI_TEXTINPUT_H__

#include "gui/Base.h"
#include "gui/Label.h"
#include "gui/FontCfg.h"
#include "input/InputEvent.h"

#include <string>

namespace Niski
{
	namespace GUI
	{
		class TextInput : public Base
		{
		public:
			TextInput(Niski::GUI::Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, const Niski::GUI::FontCfg& fontCfg);
			~TextInput(void);

			virtual void precache(Niski::Renderer::Renderer& renderer);

			virtual void render(Niski::Renderer::Renderer& renderer) const;

			// 
			// Input
			virtual void receiveKeyboardInput(const Niski::Input::InputEvent& event);
			virtual void receiveMouseMovement(const Niski::Input::MouseEvent& event);
			virtual void receiveTextInput(const std::string& str);

		private:
			Label* label_;
			Niski::Math::Vector2D<std::string::size_type> cursorPos_;
		};
	}
}

#endif