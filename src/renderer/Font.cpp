#include "renderer/Font.h"
#include <sstream>

using namespace Niski::Renderer;

Font::Font(Renderer& renderer, const std::string& typeface, int size, fontStyle style /* = Font::fontDefault */) 
	: font_(NULL), size_(size)
{
	UINT weight = (style == Font::fontBold || style == Font::fontItalicBold) ? FW_BOLD : FW_NORMAL;
	bool enableItalics = (style == Font::fontItalics || style == Font::fontItalicBold) ? true : false;

	//
	// probably should be moved to Renderer
	HRESULT result = D3DXCreateFontA(renderer.getDevice(), size, 0, weight, 1, enableItalics, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, typeface.c_str(), &font_);

	if(FAILED(result))
	{
		std::ostringstream error;
		error << "Failed to create font. \n\nDirectX returned: " << DXGetErrorString(result) << " \nDescription: " << DXGetErrorDescription(result);
		throw FontFailedToInitialize(error.str());
	}
}

Font::~Font(void)
{
	if(font_)
	{
		font_->Release();
	}
}

void Font::draw(const std::wstring& text, Niski::Math::Rect2D dimensions, Niski::Utils::Color color)
{
	//
	// TODO Should fail silently?
	if(!font_)
	{
		return;
	}

	RECT fontRect = dimensions.toWin32Rect();

	font_->DrawTextW(NULL, text.c_str(), -1, &fontRect, DT_LEFT | DT_TOP | DT_WORDBREAK, D3DXCOLOR(color.r, color.g, color.b, color.a));
}

void Font::onLost(void)
{
	if(font_)
	{
		font_->OnLostDevice();
	}
}

void Font::onReset(void)
{
	if(font_)
	{
		font_->OnResetDevice();
	}
}