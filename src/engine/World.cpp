#include "engine/World.h"

using namespace Niski::Engine;

World::World(Niski::Math::Rect2D& bounds) : Entity(nullptr, "gameWorld"), bounds_(bounds)
{}

World::~World(void)
{}

void World::setBounds(Niski::Math::Rect2D& bounds)
{
	bounds_ = bounds;
}

Niski::Math::Rect2D World::getBounds(void) const
{
	return bounds_;
}

void World::render(Niski::Renderer::Renderer& renderer) const
{
	Entity::render(renderer);
}