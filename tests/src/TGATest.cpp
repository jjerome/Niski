#include "gtest/gtest.h"
#include "renderer/RenderWindow.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "utils/TGA.h"

TEST(TGATest, Initialization)
{
	//
	// Load a file. 
	EXPECT_NO_THROW({ Niski::Utils::TGALoader tga("testData/test32bit.tga"); });

	// 
	// Load a nonexistent file
	EXPECT_THROW({ Niski::Utils::TGALoader tga("testData/doesnotExist.tga"); }, Niski::Utils::TGAFailedToLoad);
}

//
// TODO: Check the loaded textures to make sure they're valid.. 
TEST(TGATest, Load)
{
	//
	// Initialize all the stuff we need for each test.
	Niski::Renderer::RenderWindow window("Test Window", Niski::Math::Rect2D(0, 0, 720, 1280), nullptr);
	Niski::Renderer::Renderer renderer(window, Niski::Math::Vector2D<int32_t>(1280, 720), Niski::Renderer::Renderer::windowed);

	//
	// Load an uncompressed 16bit TGA
	EXPECT_THROW({
		Niski::Renderer::Texture texture;
		Niski::Utils::TGALoader tga("testData/test16bit.tga");
		tga.load(texture, renderer);
	}, Niski::Utils::TGAInvalidFormat);

	//
	// Load an uncompressed 24bit TGA
	EXPECT_NO_THROW({
		Niski::Renderer::Texture texture;
		Niski::Utils::TGALoader tga("testData/test24bit.tga");
		tga.load(texture, renderer);
	});

	//
	// Load an RLE compressed 24bit TGA
	EXPECT_NO_THROW({
		Niski::Renderer::Texture texture;
		Niski::Utils::TGALoader tga("testData/test24bitRLE.tga");
		tga.load(texture, renderer);
	});

	//
	// Load an uncompressed 32bit TGA.
	EXPECT_NO_THROW({
		Niski::Renderer::Texture texture;
		Niski::Utils::TGALoader tga("testData/test32bit.tga");
		tga.load(texture, renderer);
	});

	//
	// Load an RLE compressed 32bit TGA
	EXPECT_NO_THROW({
		Niski::Renderer::Texture texture;
		Niski::Utils::TGALoader tga("testData/test32bitRLE.tga");
		tga.load(texture, renderer);
	});
}

TEST(TGATest, IsValid)
{
	//
	// Check if an uncompressed 32bit TGA is valid
	Niski::Utils::TGALoader tga32bit("testData/test32bit.tga");
	EXPECT_TRUE(tga32bit.isValid());

	//
	// Check if an uncompressed 24bit TGA is valid
	Niski::Utils::TGALoader tga24bit("testData/test24bit.tga");
	EXPECT_TRUE(tga24bit.isValid());

	//
	// Check if an uncompressed 16bit TGA is INVALID
	Niski::Utils::TGALoader tga16bit("testData/test16bit.tga");
	EXPECT_FALSE(tga16bit.isValid());

	//
	// RLE 24bit
	Niski::Utils::TGALoader tga24bitRLE("testData/test24bitRLE.tga");
	EXPECT_TRUE(tga24bitRLE.isValid());

	//
	// RLE 32bit
	Niski::Utils::TGALoader tga32bitRLE("testData/test32bitRLE.tga");
	EXPECT_TRUE(tga32bitRLE.isValid());
}