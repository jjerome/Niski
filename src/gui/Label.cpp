#include "gui/Label.h"
#include "utils/Assert.h"

using namespace Niski::GUI;

Label::Label(Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, const std::wstring& fontFace, int16_t size) 
	: Base(parent, name), needsToPreload_(true), color_(Niski::Utils::Color::white)
{
	//
	// TODO: Should retrieve a font from our rootPanel parent
	// which will create it for us if needbe.
	font_ = new Niski::Renderer::Win32Font(fontFace, size, 0);
	Niski::Utils::Assert(font_ != nullptr, "Failed to create a font for our label.", __FILE__, __FUNCSIG__, __LINE__);

	setPosition(position);
	setSize(Niski::Math::Vector2D<int32_t>(40, 100));
}

Label::~Label(void)
{}

void Label::precache(Niski::Renderer::Renderer& renderer)
{
	if(needsToPreload_)
	{
		needsToPreload_ = !font_->preloadGlyphs(Niski::Renderer::Win32Font::ansiPreload, renderer);

		Niski::Utils::Assert(!needsToPreload_, "Niski::GUI::Label failed to preload font!", __FILE__, __FUNCSIG__, __LINE__);
	}
}

void Label::render(Niski::Renderer::Renderer& renderer) const
{
	Niski::Utils::Assert(!needsToPreload_, "Niski::GUI::Label tried to render without precaching first.", __FILE__, __FUNCSIG__, __LINE__);

	font_->render(renderer, getBounds(), text_, color_);
}

void Label::setText(const std::wstring& text)
{
	text_ = text;
}

const std::wstring& Label::getText(void) const
{
	return text_;
}

void Label::setColor(const Niski::Utils::Color& color)
{
	color_ = color;
}

const Niski::Utils::Color& Label::getColor(void) const
{
	return color_;
}

void Label::sizeToContents(void)
{
	setSize(font_->measureText(getSize(), text_));
}