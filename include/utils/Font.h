#ifndef __RENDERER_FONT_H__
#define __RENDERER_FONT_H__

#include "renderer/Renderer.h"
#include "utils/Color.h"
#include "utils/Rectangle.h"
#include <stdexcept>


namespace Niski
{
	namespace Renderer
	{
		class Font
		{
		public:
			Font(Renderer& renderer, const std::string& typeface, int size, Niski::Utils::Rect2D dimensions, bool isBold = false, bool isItalics = false);
			~Font(void);

			void draw(const std::string& text, Niski::Utils::Color color);

		private:
			ID3DXFont* font_;
			int size_;
			Niski::Utils::Rect2D dimensions_;
			bool isBold_;
			bool isItalics_;
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