#include "math/Math.h"
#include "renderer/Pixel.h"
#include "utils/Helpers.h"
#include "utils/Log.h"

using namespace Niski::Renderer;

Pixel::Pixel(Niski::Renderer::Texture* texture) : texture_(texture), pixelDesc_(texture->getPixelDescriptor()), bits_(nullptr), pitch_(0)
{
	//
	// TODO: Is this the optimal place for this? Perhaps the texture could provide this?
	switch(pixelDesc_)
	{
	case Texture::PixelDescriptor::A8R8G8B8:
		{
			pixelFormat_.bits = 32; //-V112

			pixelFormat_.redShift = 16;
			pixelFormat_.greenShift = 8;
			pixelFormat_.blueShift = 0;
			pixelFormat_.alphaShift = 24;

			pixelFormat_.redMask = 0xFF;
			pixelFormat_.greenMask = 0xFF;
			pixelFormat_.blueMask = 0xFF;
			pixelFormat_.alphaMask = 0xFF;
		}
		break;

	case Texture::R8G8B8:
		{
			pixelFormat_.bits = 32; //-V112

			pixelFormat_.redShift = 16;
			pixelFormat_.greenShift = 8;
			pixelFormat_.blueShift = 0;
			pixelFormat_.alphaShift = 0;

			pixelFormat_.redMask = 0xFF;
			pixelFormat_.greenMask = 0xFF;
			pixelFormat_.blueMask = 0xFF;
			pixelFormat_.alphaMask = 0x00;
		}
		break;

	case Texture::PixelDescriptor::A4R4G4B4:
		{
			pixelFormat_.bits = 16;

			pixelFormat_.redShift = 4; //-V112
			pixelFormat_.greenShift = 0;
			pixelFormat_.blueShift = -4; //-V112
			pixelFormat_.alphaShift = 8;

			pixelFormat_.redMask = 0xF0;
			pixelFormat_.greenMask = 0xF0;
			pixelFormat_.blueMask = 0xF0;
			pixelFormat_.alphaMask = 0xF0;
		}
		break;

	default:
		//
		// TODO: throw an exception..
		break;
	}

	//
	// Lock the entire thing. 
	try
	{
		texture_->lockRectangle(Niski::Math::Rect2D(0, 0, texture_->getHeight(), texture_->getWidth()), &bits_, pitch_);
	}
	catch(const Niski::Renderer::TextureFailedToLock& e)
	{
		//
		// TODO: Shouldn't we inform the caller that we cannot write?
		Niski::Utils::warning(e.what());
	}
}

Pixel::~Pixel(void)
{
	if(texture_)
	{
		if(texture_->isLocked())
		{
			try
			{
				texture_->unlockRectangle();
			}
			catch(const Niski::Renderer::TextureFailedToUnlock& e)
			{
				Niski::Utils::warning(e.what());
			}
		}
	}
}

void Pixel::write(const Niski::Math::Vector2D<uint32_t>& pixel, const Niski::Utils::Color& color)
{
	Niski::Math::Vector2D<uint32_t> pixelPosition(pixel);

	Niski::Math::clamp(pixelPosition.x, uint32_t(0), texture_->getWidth());
	Niski::Math::clamp(pixelPosition.y, uint32_t(0), texture_->getHeight());


	//
	// Move to the pixel where we're going to write.
	
	//
	// numBytes is the number of bytes in a row in the texture. This is determined by
	// dividing the bits by 8 to convert it from bits to bytes..
	int8_t numBytes = pixelFormat_.bits / 8;
	uint32_t* bits = bits_ + (pixelPosition.y * (pitch_ / numBytes)) + pixelPosition.x;

	unsigned int val = (color.r & pixelFormat_.redMask) << pixelFormat_.redShift;
	val |= (color.g & pixelFormat_.greenMask) << pixelFormat_.greenShift;
	val |= (color.b & pixelFormat_.blueMask) << pixelFormat_.blueShift;
	val |= (color.a & pixelFormat_.alphaMask) << pixelFormat_.alphaShift;

	switch(pixelFormat_.bits)
	{
	case 16:
		((uint16_t *)bits)[0] = (uint16_t)((val & 0xffff));
		break;

	case 24:
		((uint16_t *)bits)[0] = (uint16_t)((val & 0xffff));
		bits[2] = (uint8_t)((val >> 16) & 0xff);
		break;

	case 32:
		*bits++ = val;
		break;

	default:
		break;
	}
}

Niski::Utils::Color Pixel::read(const Niski::Math::Vector2D<uint32_t>& pixel)
{
	Niski::Math::Vector2D<uint32_t> pixelPosition(pixel);

	Niski::Math::clamp(pixelPosition.x, uint32_t(0), texture_->getWidth());
	Niski::Math::clamp(pixelPosition.y, uint32_t(0), texture_->getHeight());

	//
	// Move to the pixel where we're going to read. 
	//
	// numBytes is the number of bytes in a row in the texture. This is determined by
	// dividing the bits by 8 to convert it from bits to bytes..
	int8_t numBytes = pixelFormat_.bits / 8;
	uint32_t* bits = bits_ + (pixelPosition.y * (pitch_ / numBytes)) + pixelPosition.x;

	uint32_t val = bits[0];
	if(pixelFormat_.bits > 8)
	{
		val |= bits[1] << 8;

		if(pixelFormat_.bits > 16)
		{
			val |= bits[2] << 16;

			if(pixelFormat_.bits > 24)
			{
				val |= bits[3] << 24;
			}
		}
	}

	Niski::Utils::Color color(0, 0, 0, 0);
	color.r = (val >> pixelFormat_.redShift) & pixelFormat_.redMask;
	color.g = (val >> pixelFormat_.greenShift) & pixelFormat_.greenMask;
	color.b = (val >> pixelFormat_.blueShift) & pixelFormat_.blueMask;
	color.a = (val >> pixelFormat_.alphaShift) & pixelFormat_.alphaMask;

	return color;
}