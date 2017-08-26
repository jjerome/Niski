#include "breakaway_game/Ball.h"
#include "math/Math.h"
#include "renderer/VertexBuffer2D.h"

using namespace Niski::BreakAway;

Ball::Ball(World* world, const Niski::Math::Vector2D<float>& initialPosition, 
		   const Niski::Math::Vector2D<float>& initialVelocity, float radius) 
		   : Entity(world, "BreakAwayBall"), initialPosition_(initialPosition), 
		   initialVelocity_(initialVelocity), radius_(radius)
{
	setPosition(initialPosition);
	setVelocity(initialVelocity);
}

Ball::~Ball(void)
{}

void Ball::render(Niski::Renderer::Renderer& renderer) const
{
	//
	// TODO: Kinda dangerous..
	Niski::Renderer::VertexBuffer2D vBuffer;
	const int16_t					segments = 23;

	vBuffer.setColor(Niski::Utils::Color(Niski::Utils::Color::white));

	for(int16_t i = 0; i <= segments; ++i)
	{
		double t = (2 * Niski::Math::pi / segments) * i;
		vBuffer.pushVertex(getPosition().x + radius_ * cos(t), getPosition().y - radius_ * sin(t));
	}

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::lineList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();
}

void Ball::reset(void)
{
	setPosition(initialPosition_);
	setVelocity(initialVelocity_);
}