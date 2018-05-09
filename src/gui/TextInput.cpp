#include "gui/TextInput.h"
#include "renderer/VertexBuffer2D.h"
#include "utils/StringUtils.h"
#include "utils/Log.h"

using namespace Niski::GUI;

TextInput::TextInput(Niski::GUI::Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position) : Base(parent, name), cursorPos_(0,0)
{
	//
	// The font and size should be configurable. 
	label_ = new Label(this, name + "Label", position, "Arial", 9);
	//
	// TODO: This likely won't make it, but we're not going to
	// update the cursor position because this text is supposed 
	// to go away on focus (yet to be implemented) 
	label_->setText("Please enter some text...");
	//
	// TODO: This is nonsense. 
	label_->setBounds(Niski::Math::Rect2D(position.y, position.x, 500, 150));
	setPosition(position);
	setSize(Niski::Math::Vector2D<int32_t>(500, 150));

	label_->setColor(Niski::Utils::Color(Niski::Utils::Color::black));
}

TextInput::~TextInput(void)
{}

void TextInput::precache(Niski::Renderer::Renderer& renderer)
{
	Base::precache(renderer);
}

void TextInput::render(Niski::Renderer::Renderer& renderer) const
{
	Niski::Math::Rect2D renderRect(getBounds());
	Niski::Math::Rect2D outerRect;

	Niski::Renderer::VertexBuffer2D vBuffer;
	
	//
	// Baby blue backdrop. Yeah I hate how this
	// is currently done. The entire vBuffer system 
	// needs to be ripped out.
	vBuffer.setColor(Niski::Utils::Color(137, 207, 240, 255));
	outerRect.top = renderRect.top - 2;
	outerRect.bottom = renderRect.bottom + 2;
	outerRect.left = renderRect.left - 2;
	outerRect.right = renderRect.right + 2;
	vBuffer.pushRectangle(outerRect);

	vBuffer.setColor(Niski::Utils::Color(Niski::Utils::Color::white));
	vBuffer.pushRectangle(renderRect);

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::triangleList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();

	label_->render(renderer);
}

void TextInput::receiveKeyboardInput(const Niski::Input::InputEvent& event)
{
	//
	// We don't care about a key being released - at least at
	// the moment. 
	if(event.getKeyState() == Niski::Input::KeyState::Released)
	{
		return;
	}

	std::string str = label_->getText();

	switch (event.getKeyCode())
	{
	case Niski::Input::KeyCodes::Key_Left:
		if (cursorPos_.x > 0)
		{
			--cursorPos_.x;
		}
		break;

	case Niski::Input::KeyCodes::Key_Right:
		//
		// Still room for us to go left. 
		if (cursorPos_.x < str.length() + 1)
		{
			++cursorPos_.x;
		}
		else if (cursorPos_.y )
		{
			
		}
		break;

	case Niski::Input::KeyCodes::Key_Up:
	case Niski::Input::KeyCodes::Key_Down:
		//
		// TODO:
		break;

	case Niski::Input::KeyCodes::Key_Home:
		cursorPos_.x = 0;
		break;
		
	case Niski::Input::KeyCodes::Key_End:
		cursorPos_.x = str.length() + 1;
		break;

	case Niski::Input::KeyCodes::Key_Enter:
	case Niski::Input::KeyCodes::Key_Pad_Enter:
		str.insert(cursorPos_.x, "\n");

		//
		// TODO: Should this perform a submit?
		break;

	case Niski::Input::KeyCodes::Key_BackSpace:
		if (!str.empty())
		{
			if (cursorPos_.x != 0)
			{
				str.erase(cursorPos_.x - 1, 1);
				--cursorPos_.x;
			}
		}
		break;

	case Niski::Input::KeyCodes::Key_Delete:
		if (!str.empty() && cursorPos_.x != str.length() + 1)
		{
			str.erase(cursorPos_.x, 1);
		}
		break;

	case Niski::Input::KeyCodes::Key_Tab:
		str.insert(cursorPos_.x, "[TODO: TAB]");
		++cursorPos_.x;
		break;

	default:
		break;
	}

	//
	// Make sure our x position never goes out of bounds. 
	Niski::Math::clamp<uint32_t>(cursorPos_.x, 0, str.length() + 1);

	label_->setText(str);
}

void TextInput::receiveTextInput(std::string str)
{
	std::string data = label_->getText();

	data.insert(cursorPos_.x, str);

	label_->setText(data);

	++cursorPos_.x;
}