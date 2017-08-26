#include "pong_game/Ball.h"
#include "pong_game/Paddle.h"
#include "engine/ConVar.h"
#include "renderer/VertexBuffer2D.h"
#include "math/Math.h"
#include "utils/Log.h"

using namespace Niski::Pong_Game;

Niski::Engine::ConVar addPaddleVelocity("PongGame::Ball::AddPaddleVelocity", 0, "If enabled, when the ball collides with a paddle the y velocity of the paddle is added to the ball.");

Ball::Ball(PongWorld* world, const Niski::Math::Vector2D<float>& initialPosition, float radius) : Entity(world, "PongBall"), initialPosition_(initialPosition), radius_(radius)
{
	setPosition(initialPosition);
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
		vBuffer.pushVertex(getPosition().x + (radius_ * cos(t)), getPosition().y - (radius_ * sin(t)));
	}

	vBuffer.setPrimitiveType(Niski::Renderer::VertexBuffer2D::lineList);
	vBuffer.render(renderer);

	vBuffer.flushVertices();
}

void Ball::reset(void)
{
	setPosition(initialPosition_);
	setVelocity(Niski::Math::Vector2D<float>(0.0f, 0.0f));
}

void Ball::onTouch(Entity* ent)
{
	if(ent == nullptr)
	{
		Niski::Utils::bitch("Ball::OnTouch was called with a null ent.");

		return;
	}

	Niski::Math::Vector2D<float> position(getPosition());
	Niski::Math::Vector2D<float> newVelocity(getVelocity());

	if(ent->getName() == "Paddle")
	{
		Paddle* paddle = static_cast<Paddle*>(ent);
		Niski::Math::Vector2D<float>	paddlePosition(paddle->getPosition());
		Niski::Math::Rect2D				paddleBounds(paddle->getBounds());

		//
		// "Push" the ball out of the paddle.
		PongWorld* world = static_cast<PongWorld*>(getParent());
		if(position.x < (world->getBounds().right / 2.0f))
		{
			if(position.x < paddleBounds.left + paddleBounds.right)
			{
				position.x = paddleBounds.left + paddleBounds.right + radius_;
			}
		}
		else
		{
			if(position.x > paddleBounds.left)
			{
				position.x = paddleBounds.left - radius_;
			}
		}

		newVelocity.x = -newVelocity.x;

		if(addPaddleVelocity.getIntValue())
		{
			Niski::Math::Vector2D<float>	paddleVelocity(paddle->getVelocity());
			newVelocity.y += paddleVelocity.y;
		}
	}
	else if(ent->getName() == "gameWorld")
	{
		PongWorld* world = static_cast<PongWorld*>(ent);
		Niski::Math::Rect2D worldBounds(world->getBounds());

		{
			//
			// This method is only called if we have hit the top or the bottom 
			// since the left and right are score material and thus handled by game rules
			//
			// Collision detection doesn't happen until it's in another rectangle. 
			// so we push it out. 

			if(position.y <= worldBounds.top)
			{
				position.y = worldBounds.top + radius_;
			}
			else
			{
				position.y = worldBounds.bottom - radius_;
			}

			newVelocity.y = -newVelocity.y;
		}
	}

	setPosition(position);
	setVelocity(newVelocity);
}