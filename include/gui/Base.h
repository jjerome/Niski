#ifndef __GUI_BASE_H__
#define __GUI_BASE_H__

#include "math/Vec2d.h"
#include "math/Rectangle.h"
#include "renderer/Renderer.h"
#include <cstdint>
#include <vector>

namespace Niski
{
	namespace GUI
	{
		/*
		===============================================================================
		
			Base Widget class for all GUI items 
		
		===============================================================================
		*/

		class Base
		{
		public:
			enum Dock
			{
				default = 0,
				left,
				right,
				top,
				bottom
			};

		public:
			Base(Base* parent, const std::string& name);
			virtual ~Base(void);

			Base*							getParent(void) const;
			const std::string &				getName(void) const;

			void							addChild(Base* child);
			void							removeChild(Base* child);
			void							removeAllChildren(void);

			bool							hasChild(Base* child);
			Base*							findChild(const std::string& name);

			Base*							getChildAtPosition(const Niski::Math::Vector2D<int32_t>& position);

			Dock							getDock(void)	const;
			void							setDock(Dock dock);

			const Niski::Math::Rect2D &		getPadding(void) const;
			void							setPadding(const Niski::Math::Rect2D& padding);

			const Niski::Math::Rect2D &		getMargin(void) const;
			void							setMargin(const Niski::Math::Rect2D& margin);

			//
			// Gives the bounds but also calculates for padding. 
			const Niski::Math::Rect2D &		getInnerBounds(void) const;
			void							setInnerBounds(const Niski::Math::Rect2D& innerBounds);

			void							recalculateInnerBounds(void);
			void							performLayout(void);

			const Niski::Math::Rect2D &		getBounds(void)		const;

			//
			// TODO: These functions (and their implmentations) desperately need to be looked at
			// The functions are very misleading at the moment. There's no way to 
			// set a position relative to the parent, size isn't limited to 
			// the parent's size either. Plus size is a very shitty name
			// should be height/width -- things more commonly understood in UI programming

			//
			// Sets the bounds. Note that bounds are absolute (i.e. not relative to the parent).
			// You need to adjust 
			void							setBounds(const Niski::Math::Rect2D& bounds);

			const Niski::Math::Vector2D<int32_t>	getPosition(void)	const;
			void									setPosition(const Niski::Math::Vector2D<int32_t>& position);

			const Niski::Math::Vector2D<int32_t>	getSize(void)		const;
			void									setSize(const Niski::Math::Vector2D<int32_t>& size);

			virtual void							precache(Niski::Renderer::Renderer& renderer);
			virtual void							render(Niski::Renderer::Renderer& renderer) const;

			//
			// Input related stuff
			virtual void							receiveKeyboardInput(const Niski::Input::InputEvent& event);
			virtual void							receiveMouseButtonInput(const Niski::Input::MouseBtnEvent& event);
			virtual void							receiveMouseMovement(const Niski::Input::MouseEvent& event);
			virtual void							receiveTextInput(const std::string& str);

		private:
			Base*							parent_;
			std::string						name_;
			std::vector<Niski::GUI::Base*>	children_;
			Dock							dock_;
			Niski::Math::Rect2D				padding_;
			Niski::Math::Rect2D				margin_;
			Niski::Math::Rect2D				innerBounds_;
			Niski::Math::Rect2D				bounds_;
			bool							hovered_;
		};
	}
}

#endif