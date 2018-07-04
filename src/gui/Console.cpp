#include "gui/Console.h"

using namespace Niski::GUI;

//
// ConsoleTextInput
ConsoleTextInput::ConsoleTextInput(Niski::GUI::Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, const Niski::GUI::FontCfg& fontCfg) : TextInput(parent, name, position, fontCfg)
{}

ConsoleTextInput::~ConsoleTextInput(void)
{}

void ConsoleTextInput::receiveKeyboardInput(const Niski::Input::InputEvent& event)
{
	if (event.getKeyState() == Niski::Input::KeyState::Pressed)
	{
		if (event.getKeyCode() == Niski::Input::Key_Enter || event.getKeyCode() == Niski::Input::Key_Pad_Enter)
		{
			Console* console = reinterpret_cast<Console*>(getParent());
			console->submitInput();

			return;
		}
	}

	TextInput::receiveKeyboardInput(event);
}

Console::Console(Niski::GUI::Base* parent) : Base(parent, "Console")
{
	auto parentSize = getParent()->getSize();
	int32_t height = parentSize.y * 0.30; // Console should only overlay around 30% of the screen, roughly. 

	commandInput_ = new ConsoleTextInput(this, "ConsoleInputField", Niski::Math::Vector2D<int32_t>(0, height-20), FontCfg("Consolas", 12));
	consoleText_ = new RichText(this, "ConsoleTextDisplay", Niski::Math::Vector2D<int32_t>(0, 0), FontCfg("Consolas", 12));

	commandInput_->setSize(Niski::Math::Point(parentSize.x, 15));
	consoleText_->setSize(Niski::Math::Point(parentSize.x, height-20));

	setSize(Niski::Math::Point(parentSize.x, height));
}

Console::~Console(void)
{
	delete commandInput_;
	delete consoleText_;
}

void Console::submitInput(void)
{
	// TODO:
	printf("Console::submitInput was called!");
}

void Console::render(Niski::Renderer::Renderer& renderer) const
{
	//
	// TODO: Render a black backgroumd. 
	Niski::Math::Rect2D renderRect(getBounds());

	Niski::Renderer::VertexBuffer2D vBuffer;
	vBuffer.setColor(Niski::Utils::Color::black);
	vBuffer.pushRectangle(renderRect);

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::triangleList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();

	Base::render(renderer);
}

void Console::addLine(const std::string& str, Niski::Utils::Color col)
{
	if (consoleText_)
	{
		consoleText_->setColor(col);
		consoleText_->addLine(str);
	}
}

