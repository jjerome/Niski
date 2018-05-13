#include "gui/RichText.h"
#include "utils/Assert.h"

using namespace Niski::GUI;

RichText::RichText(Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, const FontCfg& fontCfg)
	: Base(parent, name), needsToPreload_(true), color_(Niski::Utils::Color::white)
{
	//
	// TODO: Should retrieve a font from our rootPanel parent
	// which will create it for us if needbe.

	font_ = new Niski::Renderer::Win32Font(fontCfg);
	Niski::Utils::Assert(font_ != nullptr, "Failed to create a font for our label.", __FILE__, __FUNCSIG__, __LINE__);

	setPosition(position);
	setSize(Niski::Math::Vector2D<int32_t>(40, 100));
}

RichText::~RichText(void)
{}

void RichText::precache(Niski::Renderer::Renderer& renderer)
{
	if (needsToPreload_)
	{
		needsToPreload_ = !font_->preloadGlyphs(Niski::Renderer::Win32Font::ansiPreload, renderer);

		Niski::Utils::Assert(!needsToPreload_, "Niski::GUI::Label failed to preload font!", __FILE__, __FUNCSIG__, __LINE__);
	}
}

void RichText::render(Niski::Renderer::Renderer& renderer) const
{
	Niski::Utils::Assert(!needsToPreload_, "Niski::GUI::Label tried to render without precaching first.", __FILE__, __FUNCSIG__, __LINE__);

	//
	// TODO: What a complete mess. Fix this. 
	int32_t i = std::lround(getHeight() / font_->getFontHeight());

	for (auto it = textLines_.begin(); it != textLines_.end() && i >= 0; ++it, --i)
	{
		RichTextLine data = *it;

		//
		// Shift down each time.
		auto lineBounds = getBounds();
		lineBounds.top = (lineBounds.top + getHeight()) - (i * font_->getFontHeight());
		// Make sure the font renderer doesn't attempt to draw outside of its line
		lineBounds.bottom = font_->getFontHeight();

		font_->render(renderer, lineBounds, data.str, data.col);
	}
}

void RichText::setText(const std::string& text)
{
	textLines_.clear();
	textLines_.push_back(RichTextLine(std::string(text), getColor()));
}

void RichText::addLine(const std::string& text)
{
	textLines_.push_back(RichTextLine(std::string(text), getColor()));
}

void RichText::setColor(const Niski::Utils::Color& color)
{
	color_ = color;
}

const Niski::Utils::Color& RichText::getColor(void) const
{
	return color_;
}

