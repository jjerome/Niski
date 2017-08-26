#ifndef __GUI_TEXTINPUT_H__
#define __GUITEXTINPUT_H__

#include "gui/Base.h"
#include "gui/Label.h"

#include "input/InputEvent.h"

namespace Niski
{
	namespace GUI
	{
		class TextInput : public Base
		{
		public:
			TextInput(Niski::GUI::Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position);
			~TextInput(void);

			virtual void precache(Niski::Renderer::Renderer& renderer);

			virtual void render(Niski::Renderer::Renderer& renderer) const;

			virtual void receiveKeyboardInput(const Niski::Input::InputEvent& event);

			virtual void receiveChar(wchar_t ch);

		private:
			Label* label_;
			Niski::Math::Vector2D<std::string::size_type> cursorPos_;
		};
	}
}

#endif