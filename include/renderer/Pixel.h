#ifndef __RENDERER_PIXEL_H__
#define __RENDERER_PIXEL_H__

#include "renderer/Texture.h"
#include "utils/Color.h"

namespace Niski
{
	namespace Renderer
	{
		/*
		===============================================================================
		
			Format of the pixel. Includes color shifts, color masks and the amount of 
			bits in a pixel. Data is specified in the Pixel::Pixel method.
		
		===============================================================================
		*/

		struct PixelFormat
		{
			PixelFormat() : bits(0), redShift(0), greenShift(0), blueShift(0), alphaShift(0), redMask(0), greenMask(0), blueMask(0), alphaMask(0)
			{}

			uint8_t bits;
			
			int8_t redShift;
			int8_t greenShift;
			int8_t blueShift;
			int8_t alphaShift;

			uint8_t redMask;
			uint8_t greenMask;
			uint8_t blueMask;
			uint8_t alphaMask;
		};

		/*
		===============================================================================
		
			Utility for easily reading/writing specific pixels to a specified 
			Niski::Renderer::Texture.
		
		===============================================================================
		*/

		class Pixel
		{
		public:
			Pixel(Niski::Renderer::Texture* texture);
			~Pixel(void);

			void				write(const Niski::Math::Vector2D<uint32_t>& pixel, const Niski::Utils::Color& color);
			Niski::Utils::Color read(const Niski::Math::Vector2D<uint32_t>& pixel);

			Texture::PixelDescriptor getPixelDescriptor(void) const { return pixelDesc_; }

		private:
			Niski::Renderer::Texture* texture_;
			Texture::PixelDescriptor pixelDesc_;
			PixelFormat	pixelFormat_;

			uint32_t* bits_;
			uint32_t pitch_;
		};
	}
}

#endif