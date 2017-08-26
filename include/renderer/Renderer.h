#ifndef __RENDERER_RENDERER_H__
#define __RENDERER_RENDERER_H__

#include <stdexcept>

#include "math/Vec2d.h"
#include "renderer/RenderWindow.h"
#include "utils/win32/Win32Includes.h"

typedef IDirect3DDevice9* nativeRenderer;

namespace Niski
{
	namespace Renderer
	{
		class Renderer
		{
		public:
			enum DisplayType 
			{
				windowed = 0,
				fullscreen = 1
			};

		public:
			Renderer(const RenderWindow& window, Niski::Math::Vector2D<int32_t>& backBufferSize, DisplayType displayType);
			~Renderer(void);

			nativeRenderer		getNativeRenderer(void) const;

			bool				isDeviceActive(void);
			void				resetDevice(void);

		private:
			void				initializeDevice(const RenderWindow& window, uint8_t adapter);
			void				initializePresentParams(const RenderWindow& window, uint8_t adapter, Niski::Math::Vector2D<int32_t>& backBufferSize, DisplayType displayType);

		private:
			IDirect3DDevice9* device_;
			IDirect3D9* direct3d_;
			D3DPRESENT_PARAMETERS presentParams_;
		};

		class RendererFailedToInitialize : public std::runtime_error
		{
		public:
			RendererFailedToInitialize(const std::string& error) : std::runtime_error(error)
			{}
		};

		//
		// Thrown whenever you call a method that accesses the device
		// before the device has been initialized.
		class RendererDeviceNotInitialized : public std::logic_error
		{
		public:
			RendererDeviceNotInitialized(const std::string& error) : std::logic_error(error)
			{}
		};
	}
}

#endif