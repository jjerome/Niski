#include "gui/Base.h"
#include "utils/Helpers.h"
#include "utils/StringUtils.h"

#include <iostream>

using namespace Niski::GUI;

Base::Base(Base* parent, const std::string& name) 
	: parent_(parent), 
	name_(name), 
	bounds_(0, 0, 0, 0), 
	padding_(0, 0, 0, 0), 
	margin_(0, 0, 0, 0), 
	innerBounds_(0, 0, 0, 0), 
	dock_(default)
{
	if(parent_)
	{
		parent_->addChild(this);
	}

	//
	// Set the position to the top left.. aka
	// default alignment
	setPosition(Niski::Math::Vector2D<int32_t>(0, 0));
}

Base::~Base(void)
{
	if(parent_)
	{
		parent_->removeChild(this);
	}

	if(children_.size() > 0)
	{
		removeAllChildren();
	}
}

Base* Base::getParent(void) const
{
	return parent_;
}

const std::string& Base::getName(void) const
{
	return name_;
}

void Base::addChild(Base* child)
{
	if(hasChild(child) == false)
	{
		children_.push_back(child);
	}
}

void Base::removeChild(Base* child)
{
	for(auto it = children_.begin(); it != children_.end(); ++it)
	{
		if(child == *it)
		{
			children_.erase(it);

			break;
		}
	}
}

void Base::removeAllChildren(void)
{
	auto it = children_.begin();

	while(it != children_.end())
	{
		Niski::GUI::Base* baseCtrl = *it;
		it = children_.erase(it);
		delete baseCtrl;
	}
}

bool Base::hasChild(Base* child)
{
	for(auto item : children_)
	{
		if(child == item)
		{
			return true;
		}
	}

	return false;
}

Base* Base::findChild(const std::string& name)
{
	for(auto child : children_)
	{
		if(Niski::Utils::String::toLower(child->getName()) == Niski::Utils::String::toLower(name))
		{
			return child;
		}
	}
	
	return nullptr;
}

Base* Base::getChildAtPosition(const Niski::Math::Vector2D<int32_t>& position)
{
	for(auto child : children_)
	{
		if(child->getBounds().isPointInRect<int32_t>(position))
		{
			return child;
		}
	}

	//
	// Unable to find it.
	return nullptr;
}

Base::Dock Base::getDock(void) const
{
	return dock_;
}

void Base::setDock(Dock dock)
{
	dock_ = dock;
}

const Niski::Math::Rect2D& Base::getPadding(void) const
{
	return padding_;
}

void Base::setPadding(const Niski::Math::Rect2D& padding)
{
	padding_ = padding;

	recalculateInnerBounds();
	//
	// TODO: Resize children if appropriate. 
}

const Niski::Math::Rect2D& Base::getMargin(void) const
{
	return margin_;
}

void Base::setMargin(const Niski::Math::Rect2D& margin)
{
	margin_ = margin;

	//
	// TODO: invalidate layout.. etc
}

const Niski::Math::Rect2D& Base::getInnerBounds(void) const
{
	return innerBounds_;
}

//
// TODO: This method is pointless. If they want to set the innerbounds, 
// they should just set padding to what they require
void Base::setInnerBounds(const Niski::Math::Rect2D& innerBounds)
{
	innerBounds_ = innerBounds;

	//
	// TODO: Resize children. 
}

void Base::recalculateInnerBounds(void)
{
	//
	// Calculates the inner boundary of which children should
	// offset (handles padding)
	innerBounds_.top = bounds_.top + padding_.top;
	innerBounds_.left = bounds_.left + padding_.left;
	innerBounds_.right = bounds_.right - (padding_.left + padding_.right);
	innerBounds_.bottom = bounds_.bottom - (padding_.top + padding_.bottom);
}

void Base::performLayout(void)
{
	Niski::Math::Rect2D bounds = getInnerBounds();

	for(auto child : children_)
	{
		Base::Dock dock = child->getDock();
		Niski::Math::Rect2D margin = child->getMargin();
		Niski::Math::Rect2D childBounds = child->getBounds();

		//
		// TODO: support margins and padding.. 

		switch(dock)
		{
		case Base::top:
			child->setBounds(Niski::Math::Rect2D(bounds.top, bounds.left, childBounds.bottom, bounds.right));

			bounds.top += childBounds.bottom;
			bounds.bottom -= childBounds.bottom;
			break;

		case Base::bottom:
			child->setBounds(Niski::Math::Rect2D((bounds.top + bounds.bottom) - childBounds.bottom, 
				bounds.left,
				childBounds.bottom,
				bounds.right));

			bounds.bottom -= childBounds.bottom;
			break;

		case Base::left:
			child->setBounds(Niski::Math::Rect2D(bounds.top, bounds.left, childBounds.right, bounds.bottom));

			bounds.left += childBounds.right;
			bounds.right -= childBounds.right;
			break;

		case Base::right:
			child->setBounds(Niski::Math::Rect2D(bounds.top, (bounds.left + bounds.right) - bounds.left, childBounds.right, bounds.bottom));

			bounds.right -= childBounds.right;
			break;
		}

		child->performLayout();
	}
}

const Niski::Math::Rect2D& Base::getBounds(void) const
{
	return bounds_;
}

void Base::setBounds(const Niski::Math::Rect2D& bounds)
{
	bounds_ = bounds;

	recalculateInnerBounds();
}

const Niski::Math::Vector2D<int32_t> Base::getPosition(void) const
{
	return Niski::Math::Vector2D<int32_t>(bounds_.left, bounds_.top);
}

void Base::setPosition(const Niski::Math::Vector2D<int32_t>& position)
{
	setBounds(Niski::Math::Rect2D(position.y, position.x, bounds_.bottom, bounds_.right));
}

const Niski::Math::Vector2D<int32_t> Base::getSize(void) const
{
	return Niski::Math::Vector2D<int32_t>(bounds_.right, bounds_.bottom);
}

void Base::setSize(const Niski::Math::Vector2D<int32_t>& size)
{
	setBounds(Niski::Math::Rect2D(bounds_.top, bounds_.left, size.y, size.x));
}

void Base::precache(Niski::Renderer::Renderer& renderer)
{
	if(children_.size() > 0)
	{
		for(auto item : children_)
		{
			item->precache(renderer);
		}
	}
}

void Base::render(Niski::Renderer::Renderer& renderer) const
{
	if(children_.size() > 0)
	{
		for(auto item : children_)
		{
			item->render(renderer);
		}
	}
}

void Base::receiveKeyboardInput(const Niski::Input::InputEvent& event)
{
	// todo
	Niski::Utils::UnreferencedParameter(event);
}

void Base::receiveMouseInput(const Niski::Input::InputEvent& event)
{
	// todo
	Niski::Utils::UnreferencedParameter(event);
}

void Base::receiveTextInput(std::string str)
{
	// todo
	Niski::Utils::UnreferencedParameter(str);
}