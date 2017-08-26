#include "breakaway_game/Ball.h"
#include "breakaway_game/BreakAwayBrick.h"
#include "utils/Log.h"


using namespace Niski::BreakAway;

Brick::Brick(World* world, const std::string& brickName, const Niski::Math::Vector2D<float>& position, const Niski::Utils::Color& color, int16_t health)
	: Niski::Engine::Entity(world, brickName), color_(color), health_(health)
{
	setPosition(position);
	setVelocity(Niski::Math::Vector2D<float>(0.0f, 0.0f));
}

Brick::~Brick(void)
{}

void Brick::onTouch(Niski::Engine::Entity* ent)
{
	if(ent == nullptr)
	{
		Niski::Utils::bitch("Niski::BreakAway::Brick::onTouch received a null ent");
		return;
	}

	if(ent->getName() == "BreakAwayBall")
	{
		Ball* ball = static_cast<Ball*>(ent);

		//
		// Bounce the ball back..
		// Should the ball handle that logic? Just handle its own physics with the shit it collides with?

		if(health_ < 0)
		{
			health_--;
		}
		else
		{
			//
			// TODO: Should we delete the brick from the world completely or just prevent it from rendering/colliding with the ball?
		}
	}
	else
	{
		std::ostringstream err("Niski::BreakAway::Brick::onTouch recieved an unexpected entity with name: ");
		err << ent->getName();
		Niski::Utils::bitch(err.str());
	}
}