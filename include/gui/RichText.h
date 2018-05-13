#ifndef __GUI_RICHTEXT_H__
#define __GUI_RICHTEXT_H__

#include <stack>

#include "gui/Base.h"
#include "utils/Color.h"
#include "renderer/Win32Font.h"

namespace Niski
{
	namespace GUI
	{
		struct RichTextLine
		{
		public:
			RichTextLine(std::string aStr, Niski::Utils::Color aCol) : str(aStr), col(aCol)
			{}

			std::string str;
			Niski::Utils::Color col;
		};

		class RichText : public Base
		{
		public:
			//
			// TODO: no flag support.
			RichText(Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position,
				const FontCfg& fontCfg);
			~RichText(void);

			void						precache(Niski::Renderer::Renderer& renderer);
			void						render(Niski::Renderer::Renderer& renderer) const;

			void						setText(const std::string& text);
			

			void						addLine(const std::string& text);

			void						setColor(const Niski::Utils::Color& color);
			const Niski::Utils::Color &	getColor(void) const;

			//
			// TODO: This doesn't work without a font manager. 
			void						setStyle(uint32_t style) { styleFlags_ = style; }
			uint32_t					getStyle(void) const { return styleFlags_; }

			bool						isBold(void) const { return (styleFlags_ & FontCfg::fontBold) ? true : false; }
			bool						isItalics(void) const { return (styleFlags_ & FontCfg::fontItalics) ? true : false; }
			bool						isUnderline(void) const { return (styleFlags_ & FontCfg::fontUnderline) ? true : false; }

		private:
			std::vector<RichTextLine>	textLines_;
			bool						needsToPreload_;
			Niski::Renderer::Win32Font*	font_;
			Niski::Utils::Color			color_;
			uint32_t					styleFlags_;
		};
	}
}

#endif