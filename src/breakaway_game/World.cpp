#include "breakaway_game/BreakAwayWorld.h"
#include "renderer/VertexBuffer2D.h"

using namespace Niski::BreakAway;

World::World(const Niski::Math::Rect2D& bounds, const Niski::Utils::Color& backgroundColor) : Niski::Engine::World(bounds)
{}

World::~World(void)
{}

void World::render(Niski::Renderer::Renderer& renderer) const
{
	//
	// yeah yeah i'm terrible for copy pasting. not my fault the two games are so similar 
	// and I don't feel like 2d paddles/single screen worlds are going to be terribly useful elsewhere

	//
	// We must render the world/background first, so do not draw children until
	// we're done.
	Niski::Math::Rect2D renderRect(getBounds());

	Niski::Renderer::VertexBuffer2D vBuffer;
	vBuffer.setColor(Niski::Utils::Color(19, 29, 38, 255));
	vBuffer.pushRectangle(renderRect);

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::triangleList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();

	World::render(renderer);
}