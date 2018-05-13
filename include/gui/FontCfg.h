#ifndef __GUI_FONTCFG_H__
#define __GUI_FONTCFG_H__

#include <string>
#include "utils/Color.h"

namespace Niski
{
	namespace GUI
	{
		//
		// TODO: This is a stopgap measure until we decide on how best to tackle
		struct FontCfg
		{
		public:
			enum FontStyle {
				fontNormal = (1 << 0),
				fontBold = (1 << 1),
				fontItalics = (1 << 2),
				fontUnderline = (1 << 3),
				fontStrikeout = (1 << 4),
				fontAntiAlias = (1 << 5)
			};

			FontCfg(const std::string& fntFace, int32_t fntSize, Niski::Utils::Color fntCol = Niski::Utils::Color::black, uint32_t fntFlags = FontStyle::fontNormal | FontStyle::fontAntiAlias)
				: fontFace(fntFace), fontSize(fntSize), fontColor(fntCol), fontFlags(fntFlags)
			{}

			std::string fontFace;
			Niski::Utils::Color fontColor;
			int32_t fontSize;
			uint32_t fontFlags;
		};
	}
}

#endif