#ifndef __RENDERER_TEXTURE_H__
#define __RENDERER_TEXTURE_H__

#include "math/Vec2d.h"
#include "renderer/Renderer.h"

#include <cstdint>

namespace Niski
{
	namespace Renderer
	{
		class Texture
		{
		public:
			//
			// TODO: More pixel descriptors.. 
			enum PixelDescriptor
			{
				invalidPixelDescriptor = 0,
				A8R8G8B8,
				R8G8B8,
				A4R4G4B4,
			};

		public:
			Texture(void);
			Texture(Niski::Renderer::Renderer& renderer, Niski::Math::Vector2D<uint32_t> size, PixelDescriptor pixelFormat);
			~Texture(void);

			void initialize(Niski::Renderer::Renderer& renderer, const Niski::Math::Vector2D<uint32_t>& size, PixelDescriptor pixelFormat);
			void destroy(void);

			void lockRectangle(const Niski::Math::Rect2D& lockRectangle, uint32_t** bits, uint32_t& pitch);
			void unlockRectangle(void);

			void render(Niski::Renderer::Renderer& renderer);

			PixelDescriptor getPixelDescriptor(void) const { return pixelFormat_; }

			bool isLocked(void) const { return isLocked_; }

			uint32_t getWidth(void) const { return size_.x; }
			uint32_t getHeight(void) const { return size_.y; }

		private:
			IDirect3DTexture9*	texture_;
			PixelDescriptor		pixelFormat_;
			bool				isLocked_;
			Niski::Math::Vector2D<uint32_t> size_;
		};

		//
		// Exceptions...
		class TextureFailedToInitialize : public std::runtime_error
		{
		public:
			TextureFailedToInitialize(const std::string& message) : runtime_error(message)
			{}
		};

		class TextureFailedToLock : public std::runtime_error
		{
		public:
			TextureFailedToLock(const std::string& message) : runtime_error(message)
			{}
		};

		class TextureFailedToUnlock : public std::runtime_error
		{
		public:
			TextureFailedToUnlock(const std::string& message) : runtime_error(message)
			{}
		};
	}
}

#endif