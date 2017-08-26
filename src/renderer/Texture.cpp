#include "renderer/Texture.h"
#include "utils/Helpers.h"
#include "utils/Assert.h"
#include "utils/Log.h"
#include "utils/win32/System.h"

#include <sstream>

using namespace Niski::Renderer;

Texture::Texture(void) 
	: texture_(nullptr), pixelFormat_(invalidPixelDescriptor), isLocked_(false), size_(Niski::Math::Vector2D<uint32_t>(0,0))
{}

Texture::Texture(Niski::Renderer::Renderer& renderer, Niski::Math::Vector2D<uint32_t> size, PixelDescriptor pixelFormat) 
	: texture_(nullptr), pixelFormat_(pixelFormat), isLocked_(false), size_(size)
{
	initialize(renderer, size, pixelFormat);
}

Texture::~Texture(void)
{
	if(isLocked_)
	{
		try
		{
			unlockRectangle();
		}
		catch(const TextureFailedToUnlock& e)
		{
			Niski::Utils::warning(e.what());
		}
	}

	destroy();
}

void Texture::initialize(Niski::Renderer::Renderer& renderer, const Niski::Math::Vector2D<uint32_t>& size, PixelDescriptor pixelFormat)
{
	pixelFormat_ = pixelFormat;
	size_ = size;

	D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;

	switch(pixelFormat_)
	{
	case Texture::A8R8G8B8:
		d3dFormat = D3DFMT_A8R8G8B8;
		break;

	case Texture::R8G8B8:
		d3dFormat = D3DFMT_X8R8G8B8;
		break;

	case Texture::A4R4G4B4:
		d3dFormat = D3DFMT_A4R4G4B4;
		break;

	default:
		d3dFormat = D3DFMT_UNKNOWN;
		break;
	}

	if(d3dFormat != D3DFMT_UNKNOWN)
	{
		//
		// TODO: Kinda icky - raw device access.
		HRESULT result = renderer.getNativeRenderer()->CreateTexture(size.x, size.y, 1, 0, d3dFormat, D3DPOOL_MANAGED, &texture_, nullptr);

		if(result != D3D_OK)
		{
			std::ostringstream err;
			err << "Failed to create texture.\n\nDirectX returned: ";
			err << Niski::Utils::Win32::getErrorString(result);

			throw TextureFailedToInitialize(err.str());
		}
	}
	else
	{
		throw TextureFailedToInitialize("Invalid pixel descriptor given.");
	}
}

void Texture::destroy(void)
{
	if(texture_)
	{
		texture_->Release();
	}
}

void Texture::lockRectangle(const Niski::Math::Rect2D& lockRectangle, uint32_t** bits, uint32_t& pitch)
{
	if(texture_ == nullptr)
	{
		bits = nullptr;
		pitch = 0;

		throw TextureFailedToLock("Texture is invalid.");
	}

	//
	// TODO:
	Niski::Utils::UnreferencedParameter(lockRectangle);

	D3DLOCKED_RECT lockRect;
	HRESULT result = texture_->LockRect(0, &lockRect, nullptr, 0);

	if(result != D3D_OK)
	{
		std::ostringstream err("Failed to lock texture.\n\nDirectX returned: ");
		err << Niski::Utils::Win32::getErrorString(result);

		throw TextureFailedToLock(err.str());
	}
	else
	{
		*bits = reinterpret_cast<uint32_t*>(lockRect.pBits);
		pitch = lockRect.Pitch;
		isLocked_ = true;
	}
}

void Texture::unlockRectangle(void)
{
	if(texture_ == nullptr)
	{
		throw TextureFailedToUnlock("Texture is invalid - cannot be unlocked.");
	}

	HRESULT result = texture_->UnlockRect(0);

	if(result != D3D_OK)
	{
		std::ostringstream err("Failed to unlock texture.\n\nDirectX returned: ");
		err << Niski::Utils::Win32::getErrorString(result);

		throw TextureFailedToUnlock(err.str());
	}

	isLocked_ = false;
}

//
// TODO: hmm..
void Texture::render(Niski::Renderer::Renderer& renderer)
{
	//
	// TODO: error out?
	Niski::Utils::Assert(texture_ != nullptr, "Invalid texture pointer when attempting to render", __FILE__, __FUNCSIG__, __LINE__);

	HRESULT result = renderer.getNativeRenderer()->SetTexture(0, texture_);

	//
	// TODO:
	Niski::Utils::UnreferencedParameter(result);
}