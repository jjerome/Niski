#include "gtest/gtest.h"
#include "renderer/RenderWindow.h"

TEST(RenderWindowTest, SuccessfulCreation)
{
	//
	// Construct a bordered window. 
	ASSERT_NO_THROW({ Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr, Niski::Renderer::RenderWindow::hasBorder); });

	//
	// Construct a borderless one. 
	ASSERT_NO_THROW({ Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr, Niski::Renderer::RenderWindow::noBorder); });
}

TEST(RenderWindowTest, WindowStyles)
{
	//
	// 
	Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr, Niski::Renderer::RenderWindow::hasBorder);

	//
	// Verify the window style is correct.
	EXPECT_EQ(Niski::Renderer::RenderWindow::hasBorder, window.getWindowStyle());

	//
	// Attempt to set a borderless style.
	EXPECT_NO_THROW({ window.setWindowStyle(Niski::Renderer::RenderWindow::noBorder); });

	//
	// Verify that the setting was set.
	EXPECT_EQ(Niski::Renderer::RenderWindow::noBorder, window.getWindowStyle());

	//
	// TODO: Read window style via winapi to verify it was set properly? 
}

TEST(RenderWindowTest, Titles)
{
	Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr, Niski::Renderer::RenderWindow::hasBorder);

	//
	// Attempt to read the initial title we've given it. 
	EXPECT_EQ("Test Window", window.getTitle());

	//
	// Read the window title directly via WinAPI
	char testOne_windowTitle[24];
	int result = ::GetWindowTextA(GetActiveWindow(), testOne_windowTitle, 24);

	EXPECT_TRUE(result != 0);

	EXPECT_STREQ("Test Window", testOne_windowTitle);

	//
	// Attempt to set a new title. 
	EXPECT_NO_THROW({ window.setTitle("Test"); });

	//
	// Attempt to read the new title. 
	EXPECT_EQ("Test", window.getTitle());

	//
	// Read new window title via WinAPI
	char testTwo_windowTitle[24];
	result = ::GetWindowTextA(GetActiveWindow(), testTwo_windowTitle, 24);

	EXPECT_TRUE(result != 0);

	EXPECT_STREQ("Test", testTwo_windowTitle);
}

TEST(RenderWindowTest, Dimensions)
{
	const Niski::Math::Rect2D rect720p(0, 0, 720, 1280);
	const Niski::Math::Rect2D rect480p(0, 0, 480, 640);
	Niski::Renderer::RenderWindow window("Test Window", rect720p, nullptr, Niski::Renderer::RenderWindow::hasBorder);

	//
	// Attempt to read the dimensions of the window.
	EXPECT_TRUE(rect720p == window.getDimensions());

	//
	// Read from the WinAPI to see if the dimensions are correct.
	// NOTE: Only use GetClientRect as RenderWindow automatically adjusts to get the client rect
	// to be the same as the dimensions we give it. 
	RECT clientRect;
	::GetClientRect(GetActiveWindow(), &clientRect);

	EXPECT_TRUE(EqualRect(&rect720p.toWin32Rect(), &clientRect) == TRUE);

	//
	// Set new dimensions for the window.
	EXPECT_NO_THROW({ window.setDimensions(rect480p); });

	//
	// Attempt to read new dimensions
	EXPECT_TRUE(rect480p == window.getDimensions());

	//
	// Read from WinAPI to make sure the dimensions are correct
	RECT updatedClientRect;
	::GetClientRect(GetActiveWindow(), &updatedClientRect);

	EXPECT_TRUE(EqualRect(&rect480p.toWin32Rect(), &updatedClientRect) == TRUE);
}