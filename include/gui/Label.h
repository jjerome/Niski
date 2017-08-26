#ifndef __GUI_LABEL_H__
#define __GUI_LABEL_H__

#include "gui/Base.h"
#include "renderer/Win32Font.h"

namespace Niski
{
	namespace GUI
	{
		class Label : public Base
		{
		public:
			enum StyleFlags
			{
				none = 0,
				bold = 1,
				italics = 2,
				underline = 3
			};

		public:
			//
			// TODO: no flag support.
			Label(Base* parent, const std::string& name, const Niski::Math::Vector2D<int32_t>& position, 
				const std::wstring& fontFace, int16_t size);
			~Label(void);

			void						precache(Niski::Renderer::Renderer& renderer);
			void						render(Niski::Renderer::Renderer& renderer) const;
			
			void						setText(const std::wstring& text);
			const std::wstring &		getText(void) const;

			void						setColor(const Niski::Utils::Color& color);
			const Niski::Utils::Color &	getColor(void) const;

			void						setStyle(uint32_t style) { styleFlags_ = style; }
			uint32_t					getStyle(void) const { return styleFlags_; }

			bool						isBold(void) const { return (styleFlags_ & StyleFlags::bold) ? true : false; }
			bool						isItalics(void) const { return (styleFlags_ & StyleFlags::italics) ? true : false; }
			bool						isUnderline(void) const { return (styleFlags_ & StyleFlags::underline) ? true : false; }

			void						sizeToContents(void);

		private:
			std::wstring				text_;
			bool						needsToPreload_;
			Niski::Renderer::Win32Font*	font_;
			Niski::Utils::Color			color_;
			uint32_t					styleFlags_;
		};
	}
}

#endif