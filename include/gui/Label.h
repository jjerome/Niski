#ifndef __GUI_LABEL_H__
#define __GUI_LABEL_H__

#include "gui/Base.h"
#include "utils/Color.h"
#include "renderer/Win32Font.h"

namespace Niski
{
	namespace GUI
	{
		class Label : public Base
		{
		public:
			//
			// TODO: no flag support.
			Label(Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, 
				const FontCfg& fontCfg);
			~Label(void);

			void						precache(Niski::Renderer::Renderer& renderer);
			void						render(Niski::Renderer::Renderer& renderer) const;
			
			void						setText(const std::string& text);
			const std::string &		getText(void) const;

			void						setColor(const Niski::Utils::Color& color);
			const Niski::Utils::Color &	getColor(void) const;

			//
			// TODO: This doesn't work without a font manager. 
			void						setStyle(uint32_t style) { styleFlags_ = style; }
			uint32_t					getStyle(void) const { return styleFlags_; }

			bool						isBold(void) const { return (styleFlags_ & FontCfg::fontBold) ? true : false; }
			bool						isItalics(void) const { return (styleFlags_ & FontCfg::fontItalics) ? true : false; }
			bool						isUnderline(void) const { return (styleFlags_ & FontCfg::fontUnderline) ? true : false; }

			void						sizeToContents(void);

		private:
			std::string					text_;
			bool						needsToPreload_;
			Niski::Renderer::Win32Font*	font_;
			Niski::Utils::Color			color_;
			uint32_t					styleFlags_;
		};
	}
}

#endif