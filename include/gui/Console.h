#ifndef __GUI_CONSOLE_H__
#define __GUI_CONSOLE_H__

#include "gui/TextInput.h"
#include "gui/RichText.h"
#include "gui/Base.h"
#include "renderer/VertexBuffer2D.h"

namespace Niski
{
	namespace GUI
	{
		class ConsoleTextInput : public TextInput
		{
		public:
			ConsoleTextInput(Niski::GUI::Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, const Niski::GUI::FontCfg& fontCfg);
			~ConsoleTextInput(void);

			virtual void receiveKeyboardInput(const Niski::Input::InputEvent& event);
		};

		class Console : public Base
		{
		public:
			Console(Niski::GUI::Base* parent);
			~Console(void);

			bool isActive(void) { return isActive_; }
			void toggleActive(void) { isActive_ = !isActive_; }

			void submitInput(void);

			void addLine(const std::string& str, Niski::Utils::Color col);

			virtual void render(Niski::Renderer::Renderer& renderer) const;

			// 
			// Input
#if 0 
			virtual void receiveKeyboardInput(const Niski::Input::InputEvent& event);
			virtual void receiveMouseButtonInput(const Niski::Input::MouseBtnEvent& event);
			virtual void receiveMouseMovement(const Niski::Input::MouseEvent& event);
			virtual void receiveTextInput(const std::string& str);
#endif

		private:
			bool isActive_;
			TextInput* commandInput_;
			RichText* consoleText_;
		};
	}
}

#endif