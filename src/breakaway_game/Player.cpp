#include "breakaway_game/BreakAwayPaddle.h"
#include "breakaway_game/BreakAwayPlayer.h"

using namespace Niski::BreakAway;

Player::Player(World* world, const Niski::Math::Vector2D<float>& initialPosition, bool isBot) : Niski::Engine::Player(world, "BreakAwayPlayer"), isBot_(isBot), score_(0)
{
	//
	// TODO: Make paddle, yo.
}

Player::~Player(void)
{
	//
	// TODO: Delete paddle..
}

void Player::reset(void)
{

}