#include "gtest/gtest.h"
#include "renderer/Texture.h"

TEST(TextureTests, Initialization)
{
	Niski::Renderer::RenderWindow window(L"Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr);
	Niski::Renderer::Renderer renderer(window, Niski::Math::Vector2D<int32_t>(1280, 720), Niski::Renderer::Renderer::windowed);

	EXPECT_NO_THROW({ Niski::Renderer::Texture texture(renderer, Niski::Math::Vector2D<uint32_t>(256, 256), Niski::Renderer::Texture::PixelDescriptor::A8R8G8B8); });
}

TEST(TextureTests, LockRect)
{
	Niski::Renderer::RenderWindow window(L"Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr);
	Niski::Renderer::Renderer renderer(window, Niski::Math::Vector2D<int32_t>(1280, 720), Niski::Renderer::Renderer::windowed);
	
	Niski::Renderer::Texture texture(renderer, Niski::Math::Vector2D<uint32_t>(256, 256), Niski::Renderer::Texture::PixelDescriptor::A8R8G8B8);

	uint32_t* bits;
	uint32_t pitch;
	EXPECT_NO_THROW({ texture.lockRectangle(Niski::Math::Rect2D(10, 10, 100, 100), &bits, pitch); });
}