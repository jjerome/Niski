#ifndef __RENDERER_WIN32FONT_H__
#define __RENDERER_WIN32FONT_H__

#include <string>
#include <cstdint>
#include <vector>

#include "math/Math.h"
#include "math/Rectangle.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "utils/Color.h"

namespace Niski
{
	namespace Renderer
	{
		class Win32Font
		{
		public:
			static std::string const ansiPreload;
			static Niski::Math::Vector2D<int32_t> const textureDimensions;

		public:
			//
			// Win32Font Types
			enum Styles
			{
				Bold = 1,
				Italics,
				Underline,
				Strikeout
			};


			struct GlyphSheet
			{
				GlyphSheet(void) : texture(nullptr), position(0, 0), nextY(0)
				{}

				Texture* texture;
				Niski::Math::Vector2D<int32_t> position;
				uint32_t nextY;
			};

			struct Glyph
			{
				Glyph(void) : sheetIndex(0), isValid(false), rectGlyph(0, 0, 0, 0), origin(0, 0), width(0)
				{}

				std::vector<GlyphSheet>::size_type sheetIndex;
				bool isValid;
				Niski::Math::Rect2D rectGlyph;
				Niski::Math::Vector2D<int32_t> origin;
				uint16_t width;
			};

		public:
			Win32Font(const std::string& fontFace, uint32_t size, uint32_t flags);
			~Win32Font(void);

			bool							preloadGlyphs(const std::string& glyphs, Niski::Renderer::Renderer& renderer);

			std::string					getFontFace(void)	const { return fontFace_; }
			uint32_t						getFontSize(void)	const { return fontSize_; }
			uint32_t						getFlags(void)		const { return flags_; }
			
			Niski::Math::Vector2D<int32_t>	measureText(const Niski::Math::Vector2D<int32_t>& maxSize, const std::string& text);

			void							render(Niski::Renderer::Renderer& renderer, 
				const Niski::Math::Rect2D& renderRect, 	const std::string& text, 
				const Niski::Utils::Color& color = Niski::Utils::Color::white) const;

		private:
			void findValidSheet(Niski::Renderer::Renderer& renderer, GlyphSheet* destination, uint32_t& sheetIndex, GLYPHMETRICS glyphMetrics);

		private:
			HDC dc_;
			HFONT font_;
			HBITMAP bitmap_;
			uint32_t* bits_;

			// TODO: Implement map instead. 
			//std::map<wchar_t, Glyph> glyphs_;
			Glyph glyphs_[65536];
			std::vector<GlyphSheet> glyphSheets_;
			std::string fontFace_;
			uint32_t fontSize_;
			uint32_t flags_;
			int32_t glyphSize_;
			int32_t fontHeight_;
			uint32_t ascent_;
		};

		class FailedToInitializeFont : public std::runtime_error
		{
		public:
			FailedToInitializeFont(const std::string& message) : std::runtime_error(message)
			{}
		};
	}
}

#endif