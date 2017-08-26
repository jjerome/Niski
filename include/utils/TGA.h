#ifndef __UTILS_TGA_H__
#define __UTILS_TGA_H__

#include "utils/Color.h"
#include "renderer/Texture.h"

#include <fstream>

namespace Niski
{
	namespace Utils
	{
#pragma pack(push, 1)
		class TGAHeader
		{
		public:
			uint8_t idLength;
			uint8_t colorMapType;
			uint8_t dataTypeCode;
			uint16_t colorMapOrigin;
			uint16_t colorMapLength;
			uint8_t colorMapDepth;
			uint16_t x_origin;
			uint16_t y_origin;
			uint16_t width;
			uint16_t height;
			uint8_t bitsPerPixel;
			uint8_t imageDescriptor;
		};
#pragma pack(pop)

		class TGALoader
		{
		public:
			//
			// See http://www.paulbourke.net/dataformats/tga/ for more information
			enum dataTypeCodes
			{
				noImageData = 0,
				uncompressedColorMapped = 1,
				uncompressedRGB = 2,
				uncompressedBlackAndWhite = 3,
				runLengthEncodedColorMapped = 9,
				runLengthEncodedRGB = 10,
				compressedBlackAndWhite = 11,
				compressedColorMapped = 32,
				compressedColorMapped4Pass = 33
			};

		public:
			TGALoader(const std::string& file);
			~TGALoader(void);

			void load(Niski::Renderer::Texture& texture, Niski::Renderer::Renderer& renderer);

			Niski::Renderer::Texture::PixelDescriptor getImageType(void) const;

			bool isValid(void) const;

			uint16_t getWidth(void) const;
			uint16_t getHeight(void) const;

			void readHeader(void);

		private:
			Niski::Utils::Color readPixel(const uint8_t* bytes);

		private:
			std::string		fileName_;
			std::ifstream	file_;
			bool			isHeaderLoaded_;
			TGAHeader		header_;
		};

		//
		// Exceptions
		class TGAFailedToLoad : public std::runtime_error
		{
		public:
			TGAFailedToLoad(const std::string& message) : runtime_error(message)
			{}
		};

		class TGAInvalidFormat : public std::runtime_error
		{
		public:
			TGAInvalidFormat(const std::string& message) : runtime_error(message)
			{}
		};

		class TGAWriter
		{
		public:
			TGAWriter(const std::string& fileName);
			~TGAWriter(void);

			void write(Niski::Renderer::Texture& texture, Niski::Renderer::Renderer& renderer);

		private:
			std::ofstream file_;
			TGAHeader header_;
		};
	}
}

#endif