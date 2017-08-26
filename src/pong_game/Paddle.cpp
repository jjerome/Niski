#include "pong_game/Paddle.h"
#include "renderer/VertexBuffer2D.h"

#include <cmath>

using namespace Niski::Pong_Game;

Paddle::Paddle(PongPlayer* owner, const Niski::Math::Vector2D<float>& initialPosition) 
	: Entity(owner, "Paddle"), initialPosition_(initialPosition), positionToApproach_(0.0f, 0.0f), owner_(owner)
{
	setPosition(initialPosition);
}

Paddle::~Paddle(void)
{}

void Paddle::think(double deltaTime)
{
	Entity::think(deltaTime);

	const float amount = 2.0f;
	Niski::Math::Vector2D<float> position(getPosition());
	Niski::Math::Vector2D<float> vel(getVelocity());

	if(std::fabs(position.y - positionToApproach_.y) > FLT_EPSILON)
	{
		float distance;

		if(position.y < positionToApproach_.y)
		{
			distance = std::sqrt(positionToApproach_.y - position.y);
			vel.y = std::pow(distance, amount);
		}
		else
		{
			distance = std::sqrt(position.y - positionToApproach_.y);
			vel.y = -(std::pow(distance, amount));
		}

		setVelocity(vel);
	}
}

void Paddle::reset(void)
{
	setPosition(initialPosition_);
	setVelocity(Niski::Math::Vector2D<float>(0.0f, 0.0f));
}

void Paddle::setApproachVector(const Niski::Math::Vector2D<float>& positionToApproach)
{
	positionToApproach_ = positionToApproach;
}

void Paddle::render(Niski::Renderer::Renderer& renderer) const
{
	//
	// TODO: Kinda dangerous..
	// ?????
	Niski::Math::Rect2D renderRect(getRenderBounds());

	Niski::Renderer::VertexBuffer2D vBuffer;
	vBuffer.setColor(Niski::Utils::Color(Niski::Utils::Color::white));
	vBuffer.pushRectangle(renderRect);

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::triangleList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();
}

Niski::Math::Rect2D Paddle::getBounds(void) const
{
	//
	// TODO:
	return getRenderBounds();
}

Niski::Math::Rect2D Paddle::getRenderBounds(void) const
{
	Niski::Math::Rect2D renderRect(0, 0, 0, 0);
	renderRect.top = static_cast<int32_t>(getPosition().y - 15);
	renderRect.bottom = 45;
	renderRect.left = static_cast<int32_t>(getPosition().x - 15);
	renderRect.right = 20;

	return renderRect;
}