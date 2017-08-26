#include "utils/TGA.h"
#include "renderer/Pixel.h"
#include <sstream>

using namespace Niski::Utils;

TGALoader::TGALoader(const std::string& file) : fileName_(file), isHeaderLoaded_(false)
{
	//
	// Clean our header..
	::ZeroMemory(&header_, sizeof(header_));

	file_.open(fileName_, std::fstream::binary);

	if(!file_.is_open())
	{
		throw TGAFailedToLoad("Failed to find file.");
	}

	readHeader();
}

TGALoader::~TGALoader(void)
{
	if(file_.is_open())
	{
		file_.close();
	}
}

void TGALoader::load(Niski::Renderer::Texture& texture, Niski::Renderer::Renderer& renderer)
{
	if(!isValid())
	{
		//
		//
		std::ostringstream err ("Invalid format given. Expected 2 or 10. Given ");
		err << header_.dataTypeCode;

		throw TGAInvalidFormat(err.str());
	}

	//
	// Initialize the texture. 
	texture.initialize(renderer, Niski::Math::Vector2D<uint32_t>(header_.width, header_.height), getImageType());
	Niski::Renderer::Pixel pixel(&texture);

	//
	// Seek to where we need to start reading.
	uint32_t skip = header_.idLength;
	skip += header_.colorMapType * header_.colorMapLength;

	file_.seekg(skip, std::ios_base::cur);

	Niski::Utils::Color color;
	
	//
	// Read through all the pixels
	for(int i = 0; i < header_.height; ++i)
	{
		for(int j = 0; j < header_.width; ++j)
		{
			uint8_t p[10];

			switch(header_.dataTypeCode)
			{
			case uncompressedRGB:
				{
					file_.read((char *)p, header_.bitsPerPixel / 8);

					//
					// Write to texture.
					color = readPixel(p);

					//
					// See if the image needs to be flipped.
					if(header_.imageDescriptor & 0x20) //-V112
					{
						pixel.write(Niski::Math::Vector2D<uint32_t>(j, i), color);
					}
					else
					{
						//
						// The image has to be flipped.
						pixel.write(Niski::Math::Vector2D<uint32_t>(j, header_.height - i), color);
					}
				}
				break;

			case runLengthEncodedRGB:
				{
					file_.read((char *)p, (header_.bitsPerPixel / 8) + 1);

					color = readPixel(&(p[1]));

					//
					// See if the image needs to be flipped.
					if(header_.imageDescriptor & 0x20) //-V112
					{
						pixel.write(Niski::Math::Vector2D<uint32_t>(j, i), color);
					}
					else
					{
						//
						// The image has to be flipped.
						pixel.write(Niski::Math::Vector2D<uint32_t>(j, header_.height - i), color);
					}

					//
					// Increment j
					j++;
					if(j > header_.width)
					{
						j = 0;
						i++;
						if(i > header_.height)
						{
							break;
						}
					}

					int maxK = (p[0] & 0x7f);
					
					for(int k = 1; k < maxK; ++k)
					{
						if(p[0] & 0x80)
						{
							//
							// RLE chunk
							color = readPixel(&(p[1]));

							//
							// See if the image needs to be flipped.
							if(header_.imageDescriptor & 0x20) //-V112
							{
								pixel.write(Niski::Math::Vector2D<uint32_t>(j, i), color);
							}
							else
							{
								//
								// The image has to be flipped.
								pixel.write(Niski::Math::Vector2D<uint32_t>(j, header_.height - i), color);
							}
						}
						else
						{
							//
							// Normal Chunk
							file_.read((char *)p , (header_.bitsPerPixel / 8));

							color = readPixel(p);

							//
							// See if the image needs to be flipped.
							if(header_.imageDescriptor & 0x20) //-V112
							{
								pixel.write(Niski::Math::Vector2D<uint32_t>(j, i), color);
							}
							else
							{
								//
								// The image has to be flipped.
								pixel.write(Niski::Math::Vector2D<uint32_t>(j, header_.height - i), color);
							}
						}

						//
						// Increment j
						j++;
						if(j > header_.width)
						{
							j = 0;
							i++;
							if(i > header_.height)
							{
								break;
							}
						}
					}
				}
				break;

			default:
				//
				//
				std::ostringstream err ("Invalid format given. Expected 2 or 10. Given ");
				err << header_.dataTypeCode;

				throw TGAInvalidFormat(err.str());
				break;
			}
		}
	}

}

Niski::Renderer::Texture::PixelDescriptor TGALoader::getImageType(void) const
{
	switch(header_.dataTypeCode)
	{
	case uncompressedRGB:
	case runLengthEncodedRGB:
		if(header_.bitsPerPixel == 32) //-V112
		{
			return Niski::Renderer::Texture::A8R8G8B8;
		}
		else if(header_.bitsPerPixel == 24)
		{
			return Niski::Renderer::Texture::R8G8B8;
		}
		else
		{
			//
			// TODO: support 16 bit images.
			return Niski::Renderer::Texture::invalidPixelDescriptor;
		}

	default:
		return Niski::Renderer::Texture::invalidPixelDescriptor;
		break;
	}
}

bool TGALoader::isValid() const
{
	//
	// Make sure the pixel type is correct.
	if(getImageType() != Niski::Renderer::Texture::invalidPixelDescriptor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint16_t TGALoader::getHeight(void) const
{
	return header_.height;
}

uint16_t TGALoader::getWidth(void) const
{
	return header_.width;
}

void TGALoader::readHeader(void)
{
	//
	// Read the header..
	file_.read((char *)&header_, sizeof(header_));

	// TODO: Verify header data
}

Niski::Utils::Color TGALoader::readPixel(const uint8_t* bytes)
{
	Niski::Utils::Color color;

	switch(header_.bitsPerPixel)
	{
	case 32:
		color.r = bytes[2];
		color.g = bytes[1];
		color.b = bytes[0];
		color.a = bytes[3];
		break;

	case 24:
		color.r = bytes[2];
		color.g = bytes[1];
		color.b = bytes[0];
		color.a = 255;
		break;

	default: 
		//
		// TODO:
		break;
	}

	//
	// Clamp colors just to be sure they're okay
	color.clamp(); 
	
	return color;
}