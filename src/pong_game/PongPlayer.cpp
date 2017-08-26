#include "pong_game/PongPlayer.h"
#include "pong_game/Ball.h"
#include "utils/Assert.h"

using namespace Niski::Pong_Game;

PongPlayer::PongPlayer(PongWorld* parent, const Niski::Math::Vector2D<float>& initialPaddlePosition, const std::string& name, bool isBot) 
	: Player(parent, name), isBot_(isBot), score_(0)
{
	paddle_ = new Paddle(this, initialPaddlePosition);
}

PongPlayer::~PongPlayer(void)
{
	delete paddle_;
}

void PongPlayer::reset(void)
{
	paddle_->reset();
}

void PongPlayer::setScore(int16_t score)
{
	score_ = score;
}

int16_t PongPlayer::getScore() const
{
	return score_;
}

void PongPlayer::think(const double deltaTime)
{
	Player::think(deltaTime);

	//
	// Bot code.. 
	//
	// TODO More logging... 
	if(getParent() && isBot_)
	{
		PongWorld* world = static_cast<PongWorld*>(getParent());
		Niski::Utils::Assert(world != nullptr, "Failed to get world for PongPlayer::think", __FILE__, __FUNCSIG__, __LINE__);

		Ball* ball = static_cast<Ball*>(world->findChild("PongBall"));
		Niski::Utils::Assert(ball != nullptr, "Failed to get ball for PongPlayer::think", __FILE__, __FUNCSIG__, __LINE__);
		paddle_->setApproachVector(ball->getPosition() + ball->getVelocity());
	}
}