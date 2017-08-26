#include "pong_game/PongWorld.h"
#include "renderer/VertexBuffer2D.h"

using namespace Niski::Pong_Game;

PongWorld::PongWorld(Niski::Math::Rect2D& bounds) : World(bounds)
{}

PongWorld::~PongWorld(void)
{}

void PongWorld::render(Niski::Renderer::Renderer& renderer) const
{
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