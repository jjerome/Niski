#include "engine/Entity.h"

using namespace Niski::Engine;

Entity::EntList& Entity::getEntityList(void)
{
	static EntList entList;
	return entList;
}

Entity::EntId Entity::insertEntity(Niski::Engine::Entity* ent)
{
	Entity::EntList& entList = getEntityList();

	EntId position(entList.size());
	entList.push_back(ent);

	return position;
}

void Entity::removeEntity(EntId id)
{
	Entity::EntList& entList = getEntityList();

	for(auto it = entList.begin(); it != entList.end(); ++it)
	{
		auto ent = *it;

		if(ent && ent->getId() == id)
		{
			entList.erase(it);

			return;
		}
	}
}

Entity::EntId Entity::getEntityId(Niski::Engine::Entity* ent)
{
	Entity::EntList& entList = getEntityList();

	for(auto it = entList.begin(); it != entList.end(); ++it)
	{
		if(*it == ent)
		{
			return std::distance(entList.begin(), it);
		}
	}

	//
	// Should it automatically add an entry?

	//
	// EntId has to consume the output first or we get type incompatibilites even though 
	// this should be fine in most cases. 
	return EntId(std::numeric_limits<Entity::EntId>::max);
}

Entity::Entity(Entity* parent, const std::string& name) : parent_(parent), name_(name), position_(0.0f, 0.0f), velocity_(0.0f, 0.0f)
{
	if(parent_)
	{
		parent_->addChild(this);
	}

	id_ = insertEntity(this);
}

Entity::~Entity(void)
{
	if(children_.size() > 0)
	{
		removeAllChildren();
	}

	//
	// Notify parent to remove us.
	if(parent_)
	{
		parent_->removeChild(this);
	}

	removeEntity(id_);
}

void Entity::setParent(Entity* parent)
{
	if(parent_)
	{
		parent_->removeChild(this);
	}

	parent_ = parent;
}

Entity* Entity::getParent(void) const
{
	return parent_;
}

Entity::EntId Entity::getId(void) const
{
	return id_;
}

void Entity::setName(const std::string& name)
{
	name_ = name;
}

const std::string& Entity::getName(void) const
{
	return name_;
}

void Entity::setPosition(const Niski::Math::Vector2D<float>& position)
{
	position_ = position;
}

const Niski::Math::Vector2D<float>& Entity::getPosition(void) const
{
	return position_;
}

void Entity::setVelocity(const Niski::Math::Vector2D<float>& velocity)
{
	velocity_ = velocity;
}

const Niski::Math::Vector2D<float>& Entity::getVelocity(void) const
{
	return velocity_;
}

void Entity::think(const double deltaTime)
{
	if(children_.size() > 0)
	{
		for(auto ent : children_)
		{
			ent->think(deltaTime);
		}
	}

	position_ += velocity_ * float((deltaTime * 10.0));
}

void Entity::render(Niski::Renderer::Renderer& renderer) const
{
	if(children_.size() > 0)
	{
		for(auto ent : children_)
		{
			ent->render(renderer);
		}
	}
}

void Entity::addChild(Entity* child)
{
	if(hasChild(child) == false)
	{
		children_.push_back(child);
	}
}

void Entity::removeChild(Entity* child)
{
	if(children_.size() > 0)
	{
		for(auto it = children_.begin(); it != children_.end(); ++it)
		{
			if(child == *it)
			{
				children_.erase(it);

				return;
			}
		}
	}
}

void Entity::removeAllChildren(void)
{
	if(children_.size() > 0)
	{
		auto it = children_.begin();

		while(it != children_.end())
		{
			Niski::Engine::Entity* ent = *it;
			it = children_.erase(it);
			delete ent;
		}
	}
}

Entity* Entity::findChild(const std::string& name)
{
	if(children_.size() > 0)
	{
		for(auto it : children_)
		{
			if(it->getName() == name)
			{
				return it;
			}
		}
	}
	
	return nullptr;
}

bool Entity::hasChild(Entity* child)
{
	if(children_.size() > 0)
	{
		for(auto it : children_)
		{
			if(child == it)
			{
				return true;
			}
		}
	}
	
	return false;
}