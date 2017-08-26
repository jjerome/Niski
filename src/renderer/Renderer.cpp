#include "renderer/Renderer.h"
#include "utils/Debug.h"
#include "utils/Helpers.h"
#include "utils/win32/System.h"
#include <iostream>
#include <sstream>

using namespace Niski::Renderer;

typedef IDirect3D9* (WINAPI *D3DCreate9)(UINT);

Renderer::Renderer(const RenderWindow& window, Niski::Math::Vector2D<int32_t>& backBufferSize, DisplayType displayType)
{
	auto d3d9 = ::LoadLibrary(L"d3d9.dll");

	if (d3d9 == INVALID_HANDLE_VALUE)
	{
		throw RendererFailedToInitialize("Failed to load d3d9.dll. Install a DirectX redistributable from Microsoft.");
	}

	auto d3d9CreatePtr = (D3DCreate9)(::GetProcAddress(d3d9, "Direct3DCreate9"));

	direct3d_ = d3d9CreatePtr(D3D_SDK_VERSION);

	if(direct3d_ == nullptr)
	{
		throw RendererFailedToInitialize("Failed to create Direct3D object.");
	}

	::ZeroMemory(&presentParams_, sizeof(presentParams_));
	initializePresentParams(window, D3DADAPTER_DEFAULT, backBufferSize, displayType);
	initializeDevice(window, D3DADAPTER_DEFAULT);
}

Renderer::~Renderer(void)
{
	if(device_)
	{
		device_->Release();
	}

	if(direct3d_)
	{
		direct3d_->Release();
	}
}

nativeRenderer Renderer::getNativeRenderer(void) const
{
	if(device_ == nullptr)
	{
		throw RendererDeviceNotInitialized("Niski::Renderer::Renderer::getDevice called before device was initialized");
	}

	return device_;
}

//
// TODO: This method needs to be more specific in what it returns - i.e. if a device can currently be reset or not.
bool Renderer::isDeviceActive(void)
{
	if(device_ == nullptr)
	{
		throw RendererDeviceNotInitialized("Niski::Renderer::Renderer::isDeviceActive called before device was initialized");
	}

	HRESULT result = device_->TestCooperativeLevel();

	if(result == D3D_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
// Return a boolean value to state whether or not the device reset?
// TODO: What about when the device simply cannot be reset?
void Renderer::resetDevice(void)
{
	if(device_ == nullptr)
	{
		throw RendererDeviceNotInitialized("Niski::Renderer::Renderer::resetDevice was called before device was initialized");
	}

	HRESULT result = device_->TestCooperativeLevel();

	switch(result)
	{
	case D3DERR_DEVICENOTRESET:
		{
			HRESULT resetResult = device_->Reset(&presentParams_);

			//
			// TODO:
			Niski::Utils::UnreferencedParameter(resetResult);

			return;
		}
	//
	// We need to wait before we can reset with this. 
	case D3DERR_DEVICELOST:
		return;
	
	case D3D_OK:
	default:
		return;
	}
}

void Renderer::initializeDevice(const RenderWindow& window, uint8_t adapter)
{
	D3DCAPS9 deviceCaps;
	HRESULT result = direct3d_->GetDeviceCaps(adapter, D3DDEVTYPE_HAL, &deviceCaps);

	if(FAILED(result))
	{
		std::ostringstream error;
		error << "Failed to get device capabilities. \n\nDirectX returned: " << Niski::Utils::Win32::getErrorString(result);
		throw RendererFailedToInitialize(error.str());
	}

	DWORD vertexProcessing;

	if(deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	result = direct3d_->CreateDevice(adapter, D3DDEVTYPE_HAL, window.getNativeHandle(), vertexProcessing | D3DCREATE_MULTITHREADED, &presentParams_, &device_);

	if(FAILED(result))
	{
		std::ostringstream error;
		error << "Failed to initialize device. \n\nDirectX returned: " << Niski::Utils::Win32::getErrorString(result);
		throw RendererFailedToInitialize(error.str());
	}

	device_->BeginScene();
		device_->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 50, 75), 1.0f, 0);
	device_->EndScene();
}

void Renderer::initializePresentParams(const RenderWindow& window, uint8_t adapter, Niski::Math::Vector2D<int32_t>& backBufferSize, DisplayType displayType)
{
	// 
	//  TODO should enumerate across all the adapters and choose the correct display mode format or some shit. 
	D3DDISPLAYMODE displayMode;
	HRESULT result = direct3d_->GetAdapterDisplayMode(adapter, &displayMode);

	if(FAILED(result))
	{
		std::ostringstream error;
		error << "Failed to get adapter display mode. \n\nDirectX returned: " << Niski::Utils::Win32::getErrorString(result);
		throw RendererFailedToInitialize(error.str());
	}

	D3DFORMAT backBufferFormat = displayMode.Format;
	result = direct3d_->CheckDeviceFormat(adapter, D3DDEVTYPE_HAL, displayMode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, backBufferFormat);

	if(FAILED(result))
	{
		std::ostringstream error;
		//
		// TODO More relevant error
		error << "Failed to validate backbuffer format. \n\nDirectX returned: " << Niski::Utils::Win32::getErrorString(result);
		throw RendererFailedToInitialize(error.str());
	}

	D3DFORMAT depthFormats[] = 
	{
		D3DFMT_D32,
		D3DFMT_D24X8,
		D3DFMT_D24S8,
		D3DFMT_D24X4S4,
		D3DFMT_D16,
		D3DFMT_D15S1
	};
	D3DFORMAT depthFormatSelected = D3DFMT_UNKNOWN;

	for(auto currentFormat : depthFormats)
	{
		if(FAILED(direct3d_->CheckDeviceFormat(adapter, D3DDEVTYPE_HAL, backBufferFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, currentFormat)))
		{
			continue;
		}

		if(FAILED(direct3d_->CheckDepthStencilMatch(adapter, D3DDEVTYPE_HAL, backBufferFormat, backBufferFormat, currentFormat)))
		{
			continue;
		}

		depthFormatSelected = currentFormat;

		break;
	}

	if(depthFormatSelected == D3DFMT_UNKNOWN)
	{
		std::ostringstream error;
		//
		// TODO More relevant error
		error << "Failed to find valid depth stencil format. \n\nDirectX returned: " << Niski::Utils::Win32::getErrorString(result);
		throw RendererFailedToInitialize(error.str());
	}

	presentParams_.Windowed = (displayType == Renderer::windowed);
	presentParams_.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParams_.hDeviceWindow = window.getNativeHandle();
	presentParams_.BackBufferHeight = backBufferSize.y;
	presentParams_.BackBufferWidth = backBufferSize.x;
	presentParams_.BackBufferFormat = backBufferFormat;
	presentParams_.BackBufferCount = 1;
	presentParams_.AutoDepthStencilFormat = depthFormatSelected;
	presentParams_.EnableAutoDepthStencil = true;
	presentParams_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	presentParams_.MultiSampleQuality = 0;
	presentParams_.MultiSampleType = D3DMULTISAMPLE_NONE;
}