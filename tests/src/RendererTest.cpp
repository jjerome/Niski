#include "gtest/gtest.h"
#include "renderer/Renderer.h"
#include "utils/win32/System.h"

TEST(RendererTest, Initialization)
{
	{
		//
		// Initialize a standard windowed renderer
		Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr);
		EXPECT_NO_THROW({ Niski::Renderer::Renderer renderer(window, Niski::Math::Vector2D<int32_t>(1280, 720), Niski::Renderer::Renderer::windowed); });
	}

	{
		//
		// Initialize a fullscreen renderer
		Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 0, 0), nullptr);
		auto desktopResolution = Niski::Utils::Win32::getDesktopResolution();
		EXPECT_NO_THROW({ Niski::Renderer::Renderer renderer(window, desktopResolution, Niski::Renderer::Renderer::fullscreen); });
	}
}

TEST(RendererTest, DeviceReset)
{
	//
	// Initialize a fullscreen renderer (since windowed devices do not reset 
	// when you switch to another window).
	Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 0, 0), nullptr);
	auto desktopResolution = Niski::Utils::Win32::getDesktopResolution();
	Niski::Renderer::Renderer renderer(window, desktopResolution, Niski::Renderer::Renderer::fullscreen);

	//
	// Set a new active window. 
	
	//
	// Check if the device needs to be reset (it should)

	//
	// Set our window as active again

	//
	// Attempt to reset the device
	
	//
	// Check again if the device needs to be reset (it shouldn't)

}