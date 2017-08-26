#ifndef __RENDERER_FONT_H__
#define __RENDERER_FONT_H__

#include <stdexcept>

#include "renderer/Renderer.h"
#include "utils/Color.h"
#include "math/Rectangle.h"

namespace Niski
{
	namespace Renderer
	{
		class Font
		{
		public:
			enum fontStyle
			{
				fontDefault = 0,
				fontBold,
				fontItalics,
				fontItalicBold,
			};

		public:
			Font(Renderer& renderer, const std::string& typeface, int size, fontStyle style = Font::fontDefault);
			~Font(void);

			void draw(const std::wstring& text, Niski::Math::Rect2D dimensions, Niski::Utils::Color color);
			void onLost(void);
			void onReset(void);

		private:
			/*ID3DXFont* font_;*/
			int size_;
		};

		class FontFailedToInitialize : public std::runtime_error
		{
		public:
			FontFailedToInitialize(const std::string& error) : std::runtime_error(error)
			{}
		};
	}
}

#endif