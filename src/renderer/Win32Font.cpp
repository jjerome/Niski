#include "renderer/Win32Font.h"
#include "renderer/VertexBuffer2D.h"
#include "utils/debug/imdebug.h"
#include "utils/Assert.h"
#include "utils/Log.h"
#include <sstream>

using namespace Niski::Renderer;

//
// TODO: Hack
const std::string Win32Font::ansiPreload = "?!@#$%^&*()-_=+[{]}\\|'\";:/.>,<`~ ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

Win32Font::Win32Font(const std::string& fontFace, uint32_t size, uint32_t flags) 
	: dc_(nullptr), font_(nullptr), bitmap_(nullptr), bits_(nullptr), fontFace_(fontFace), fontSize_(size), flags_(flags)
{
	int weight = (flags & Styles::Bold) ? FW_BOLD : FW_NORMAL;
	bool italics = (flags & Styles::Italics) ? true : false;
	bool underline = (flags & Styles::Underline) ? true : false;
	bool strikeout = (flags & Styles::Strikeout) ? true : false;

	//
	// initialize GDI stuff.
	dc_ = ::CreateCompatibleDC(nullptr);

	if(dc_ == nullptr)
	{
		std::ostringstream err("Failed to create GDI device context. \nWindows API returned error code: ");
		err << ::GetLastError();
		throw FailedToInitializeFont(err.str());
	}

	//
	// Make the height negative because the size we get is not in device units
	int32_t height = -(::MulDiv(size, ::GetDeviceCaps(dc_, LOGPIXELSY), 72));

	font_ = ::CreateFontA(height, 0, 0, 0, weight, italics, underline, strikeout, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, fontFace.c_str());

	if(font_ == nullptr)
	{
		std::ostringstream err("Failed to create font writer for ");
		// TODO: Once we have a wide -> byte utility function this should
		// be updated.. 
		//err << fontFace;
		err << "\nWindows API returned error code: ";
		err << ::GetLastError();
		throw FailedToInitializeFont(err.str());
	}

	int result = ::SetMapMode(dc_, MM_TEXT);

	if(result == 0)
	{
		std::ostringstream err("Failed to Set Map Mode for our GDI device context. \nWindows API returned error code: ");
		err << ::GetLastError();
		throw FailedToInitializeFont(err.str());
	}

	::SelectObject(dc_, font_);
	::SetTextAlign(dc_, TA_LEFT | TA_TOP | TA_UPDATECP);

	TEXTMETRIC tm;
	::ZeroMemory(&tm, sizeof(tm));

	if(::GetTextMetrics(dc_, &tm) == FALSE)
	{
		std::ostringstream err("Failed to get metrics for font. \nWindows API returned error code: ");
		err << ::GetLastError();
		throw FailedToInitializeFont(err.str());
	}

	fontHeight_ = tm.tmHeight + tm.tmExternalLeading + 1;
	ascent_ = tm.tmAscent;

	//
	// Determine the size of our bitmap. 
	glyphSize_ = Niski::Math::roundUpToPowerOfTwo(max(fontHeight_, tm.tmMaxCharWidth));
	glyphSize_ = max(glyphSize_, 32); //-V112

	BITMAPINFO bitMapInfo;
	::ZeroMemory(&bitMapInfo, sizeof(bitMapInfo));
	bitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitMapInfo.bmiHeader.biWidth = glyphSize_;
	bitMapInfo.bmiHeader.biHeight = (glyphSize_) * -1;
	bitMapInfo.bmiHeader.biPlanes = 1;
	bitMapInfo.bmiHeader.biBitCount = 32; //-V112
	bitMapInfo.bmiHeader.biCompression = BI_RGB;

	bitmap_ = ::CreateDIBSection(dc_, &bitMapInfo, DIB_RGB_COLORS, (void**)&bits_, nullptr, 0);

	if(bitmap_ == nullptr)
	{
		std::ostringstream err("Failed to create a DIB for font rendering. \nWindows API returned error code: ");
		err << ::GetLastError();
		throw FailedToInitializeFont(err.str());
	}

	::SelectObject(dc_, bitmap_);
	::SetBkColor(dc_, RGB(0, 0, 0));
	::SetTextColor(dc_, RGB(255, 255, 255));
}

Win32Font::~Win32Font(void)
{
	if(dc_)
	{
		::DeleteDC(dc_);
	}

	if(font_)
	{
		::DeleteObject(font_);
	}

	if(bitmap_)
	{
		::DeleteObject(bitmap_);
	}

	//
	// Release all of our sheets
	if(glyphSheets_.size() > 0)
	{
		for(auto glyph : glyphSheets_)
		{
			if(glyph.texture)
			{
				glyph.texture->destroy();
			}
		}
	}
}

bool Win32Font::preloadGlyphs(const std::string& glyphs, Niski::Renderer::Renderer& renderer)
{
	//
	// TODO: This function is far too complex..
	bool ret = true;

	Texture* lockedSheet = nullptr;
	uint32_t* lockedBits = nullptr;
	uint32_t pitch = 0;
	size_t sheetIndex = 0;	
	HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	D3DLOCKED_RECT lockedRect;
	::ZeroMemory(&lockedRect, sizeof(lockedRect));
	
	//
	// Set our font to render to the dib
	::SelectObject(dc_, font_);

	for(wchar_t ch : glyphs)
	{
		//
		// Check if we've already rendered this glyph
		if(glyphs_[ch].isValid)
		{
			continue;
		}

		//
		// Have the bitmap be written to from the top left.
		::MoveToEx(dc_, 0, 0, nullptr);

		//
		// Reset the bitmap to being fully black
		RECT rect = {0, 0, glyphSize_, glyphSize_};
		::FillRect(dc_, &rect, brush);

		//
		// Set text color to white again, just to be safe. 
		::SetTextColor(dc_, RGB(255, 255, 255));
		
		//
		// Draw this glyph onto the DC
		if(::DrawText(dc_, &ch, 1, &rect, DT_LEFT | DT_TOP | DT_SINGLELINE) == 0)
		{
			std::ostringstream err("Failed to DrawText to the bitmap. \nWindows API returned error code: ");
			err << ::GetLastError();
			// 
			// TODO: Throw an exception?

			ret = false;

			break;
		}

		GLYPHMETRICS glyphMetrics;
		MAT2 mat;
		::ZeroMemory(&mat, sizeof(mat));
		mat.eM11.value = 1;
		mat.eM22.value = 1;

		if(::GetGlyphOutline(dc_, ch, GGO_METRICS, &glyphMetrics, 0, nullptr, &mat) == GDI_ERROR)
		{
			SIZE sizeGlyph;

			if(::GetTextExtentPoint32(dc_, &ch, 1, &sizeGlyph) == 0)
			{
				std::ostringstream err("Failed to obtain text information. \nWindows API returned error code: ");
				err << ::GetLastError();

				Niski::Utils::bitch(err.str());

				ret = false;

				break;
			}

			::ZeroMemory(&glyphMetrics, sizeof(glyphMetrics));
			glyphMetrics.gmBlackBoxX = sizeGlyph.cx;
			glyphMetrics.gmBlackBoxY = sizeGlyph.cy;
			glyphMetrics.gmptGlyphOrigin.x = 0;
			glyphMetrics.gmptGlyphOrigin.y = ascent_;
			glyphMetrics.gmCellIncX = (short)sizeGlyph.cx;
		}

		//
		// Find a sheet with empty space for our glyph. 
		GlyphSheet* sheet = nullptr;
		for(size_t i = 0; i < glyphSheets_.size(); ++i)
		{
			GlyphSheet& currentSheet = glyphSheets_[i];

			if(currentSheet.position.x + glyphMetrics.gmBlackBoxX <= 256)
			{
				if(currentSheet.position.y + glyphMetrics.gmBlackBoxY <= 256)
				{
					sheetIndex = i;
					sheet = &currentSheet;

					break;
				}
			}
			else
			{
				if(currentSheet.nextY + glyphMetrics.gmBlackBoxY <= 256)
				{
					currentSheet.position.x = 0;
					currentSheet.position.y = currentSheet.nextY;
					sheet = &currentSheet;
					sheetIndex = i;

					break;
				}
			}
		}

		//
		// If we found no acceptable sheet, create our own
		if(sheet == nullptr)
		{
			GlyphSheet newSheet;
			
			newSheet.texture = new Texture(renderer, Niski::Math::Vector2D<uint32_t>(256, 256), Niski::Renderer::Texture::A8R8G8B8);

			if(lockedSheet)
			{
				lockedSheet->unlockRectangle();
			}

			lockedSheet = nullptr;

			newSheet.nextY = 0;

			sheetIndex = glyphSheets_.size();
			glyphSheets_.push_back(newSheet);
			sheet = &glyphSheets_.back();
		}

		//
		// Check if the locked sheet we have is the one we're planning to write to
		// if not, then close it. 
		if(lockedSheet != sheet->texture)
		{
			if(lockedSheet)
			{
				lockedSheet->unlockRectangle();
			}

			sheet->texture->lockRectangle(Niski::Math::Rect2D(-1, -1, -1, -1), &lockedBits, pitch);
		
			lockedSheet = sheet->texture;
		}

		Niski::Math::Vector2D<int32_t> offset(sheet->position);
		sheet->position.x += glyphMetrics.gmBlackBoxX + 1;

		//
		// If this character is taller than previous ones, then update nextY
		if(glyphMetrics.gmBlackBoxY > sheet->nextY - sheet->position.y)
		{
			sheet->nextY = sheet->position.y + glyphMetrics.gmBlackBoxY;
		}

		//
		// Need to make sure everything is written to the bitmap
		// before reading
		::GdiFlush();

		//
		// Advance our pointer to where we're supposed to be
		uint32_t* dwordBits = lockedBits + (offset.y * (pitch / 4)) + (offset.x); //-V112

#if 0
		imdebug("argb w=%d h=%d b=8 %p", glyphSize_, glyphSize_, bits_);
#endif

		//
		// Copy bitmap to the texture..
		int yMax = ascent_ - glyphMetrics.gmptGlyphOrigin.y + glyphMetrics.gmBlackBoxY;
		int xMax = glyphMetrics.gmptGlyphOrigin.x + glyphMetrics.gmBlackBoxX;
		for(int y = ascent_ - glyphMetrics.gmptGlyphOrigin.y; y < yMax; ++y)
		{
			for(int x = 0; x < xMax; ++x)
			{
				uint32_t val; 
				val = (bits_[y * glyphSize_ + x] & 0xFF) << 16;
				val |= (bits_[(y * glyphSize_ + x)] & 0xFF) << 8;
				val |= (bits_[(y * glyphSize_ + x)] & 0xFF) << 0;
				val |= (bits_[(y * glyphSize_ + x)] & 0xFF) << 24;

				*dwordBits++ = val;
			}

			//
			// Pitch is the number of bytes in a row, so we divide it by
			// 4 (because our texture is 32bits per pixel 32 / 8 = 4)..
			dwordBits += (pitch / 4) - xMax;
		}

		glyphs_[ch].sheetIndex = sheetIndex;
		glyphs_[ch].isValid = true;
		glyphs_[ch].rectGlyph.left = offset.x;
		glyphs_[ch].rectGlyph.top = offset.y;
		glyphs_[ch].rectGlyph.right = glyphMetrics.gmptGlyphOrigin.x + glyphMetrics.gmBlackBoxX;
		glyphs_[ch].rectGlyph.bottom = glyphMetrics.gmBlackBoxY;
		glyphs_[ch].origin = Niski::Math::Vector2D<int32_t>(glyphMetrics.gmptGlyphOrigin.x, glyphMetrics.gmptGlyphOrigin.y);
		glyphs_[ch].width = glyphMetrics.gmCellIncX;
	}

	if(lockedSheet && lockedSheet->isLocked())
	{ 
		lockedSheet->unlockRectangle();
	}

	return ret;
}

Niski::Math::Vector2D<int32_t> Win32Font::measureText(const Niski::Math::Vector2D<int32_t>& maxSize, const std::string& text)
{
	Niski::Math::Vector2D<int32_t> size(0, fontHeight_);

	for(wchar_t ch : text)
	{
		//
		// TODO: Hack. Needs to handle all special characters appropriately (\t)
		if(ch == '\n')
		{
			if(maxSize.y == 0 || (size.y + fontHeight_ <= maxSize.y))
			{
				size.y += fontHeight_;
			}
			else
			{
				//
				// We cannot fit any more text, so just quit out. 
				break;
			}
		}
		else if(glyphs_[ch].isValid)
		{
			if(maxSize.x == 0 || (size.x + glyphs_[ch].width <= maxSize.x))
			{
				size.x += glyphs_[ch].width;
			}
			else if(maxSize.y == 0 || (size.y + fontHeight_ <= maxSize.y))
			{
				size.y += fontHeight_;
			}
			else
			{
				//
				// We cannot fit any more text, so just quit out. 
				break;
			}
		}
	}

	return size;
}

void Win32Font::render(Niski::Renderer::Renderer& renderer, const Niski::Math::Rect2D& renderRect, 
					   const std::string& text, const Niski::Utils::Color& color) const
{
	//
	// TODO: fix support for letters that go below the line, typically. 
	// Perhaps measure the text instead of using glyph size? 
	size_t currentSheet = -1;
	Niski::Math::Vector2D<int32_t> position(renderRect.left, renderRect.top + fontHeight_);
	Niski::Renderer::VertexBuffer2D vBuffer;
	IDirect3DDevice9* device = renderer.getNativeRenderer();
	vBuffer.setColor(color);

	for(wchar_t ch : text)
	{
		Glyph glyph = glyphs_[ch];

		//
		// Check if we have room for this character
		// TODO: Support for word breaks rather than character breaks..
		if(position.x + glyph.width > renderRect.left + renderRect.right)
		{
			//
			// Check if we have room for another line..
			if(position.y + fontHeight_ > renderRect.top + renderRect.bottom)
			{
				//
				// No room left.. just quit drawing. 
				break;
			}
			else
			{
				position.y += fontHeight_;
				position.x = renderRect.left;
			}
		}

		//
		// Special check for new lines
		if(ch == '\n')
		{
			// Check if we have room for a new line
			if(position.y + fontHeight_ > renderRect.top + renderRect.bottom)
			{
				//
				// No room left... abort drawing the rest. 
				break;
			}
			else
			{
				position.y += fontHeight_;
				position.x = renderRect.left;
			}
		}

		//
		// Draw the character if it needs it. 
		if(glyph.isValid)
		{
			Niski::Math::Rect2D rect(glyph.rectGlyph);
			Niski::Math::Rect2D glyphRect;

			// 
			// The top of the rectangle should be the height of the character from the bottom.
			glyphRect.top = position.y - glyph.origin.y;
			glyphRect.bottom = rect.bottom;
			glyphRect.left = position.x;
			glyphRect.right = rect.right;

			vBuffer.pushTexturedRectangle(glyphRect, rect.left / 256.0f, rect.top / 256.0f, (rect.left + rect.right) / 256.0f, (rect.top + rect.bottom) / 256.0f);

			{
				device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

				if(currentSheet != glyph.sheetIndex)
				{
					currentSheet = glyph.sheetIndex;
					glyphSheets_[currentSheet].texture->render(renderer);
				}

				vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::triangleList);
				vBuffer.render(renderer);
			}

			vBuffer.flushVertices();
		}

		//
		// Update the current position
		// TODO: kind of icky. 
		if(ch != '\n')
		{
			position.x += glyph.width;
		}
	}

	//
	// Set the texture to nullptr for other things to render..
	// TODO: fix when texture system is up. 
	renderer.getNativeRenderer()->SetTexture(0, nullptr);
}