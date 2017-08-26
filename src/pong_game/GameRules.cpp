#include "pong_game/GameRules.h"
#include "math/Random.h"
#include "utils/Assert.h"
#include "utils/Log.h"

using namespace Niski::Pong_Game;

void PauseCmd::run(void)
{
	if(gameRules_)
	{
		gameRules_->pause();
	}
}

void ResetCmd::run(void)
{
	if(gameRules_)
	{
		gameRules_->reset();
		gameRules_->start();
	}
}

GameRules::GameRules(void) : world_(nullptr), ball_(nullptr), needReset_(false), isPaused_(false), resetCmd_(this), pauseCmd_(this)
{}

GameRules::~GameRules(void)
{
	//
	// Remove everything.
	delete ball_;

	if(players_.size() > 0)
	{
		auto it = players_.begin();

		while(it != players_.end())
		{
			PongPlayer* player = *it;
			it = players_.erase(it);
			delete player;
		}
	}

	//
	// World must be removed last
	delete world_;
}

void GameRules::createGameWorld(Niski::Math::Rect2D& bounds)
{
	world_ = new PongWorld(bounds);
}

PongPlayer* GameRules::createPlayer(const std::string& name, float x)
{
	Niski::Utils::Assert(world_ != nullptr, "Failed to create a player, because the world was nullptr!", __FILE__, __FUNCSIG__, __LINE__);

	Niski::Math::Vector2D<float> initialPosition(x, static_cast<float>(world_->getBounds().bottom / 2));

	PongPlayer* player = new PongPlayer(world_, initialPosition, name, false);
	players_.push_back(player);

	return player;
}

PongPlayer* GameRules::createBot(float x)
{
	Niski::Utils::Assert(world_ != nullptr, "Failed to create a bot, because the world was nullptr!", __FILE__, __FUNCSIG__, __LINE__);

	Niski::Math::Vector2D<float> initialPosition(x, static_cast<float>(world_->getBounds().bottom / 2));

	std::string name = "BOT_PLAYER";

	PongPlayer* player = new PongPlayer(world_, initialPosition, name, true);
	players_.push_back(player);

	return player;
}

Ball* GameRules::createBall(void)
{
	Niski::Utils::Assert(world_ != nullptr, "Failed to create a ball, because the world was nullptr!", __FILE__, __FUNCSIG__, __LINE__);

	Niski::Math::Vector2D<float> initialPosition(static_cast<float>(world_->getBounds().right / 2), static_cast<float>(world_->getBounds().bottom / 2));

	ball_ = new Ball(world_, initialPosition, 6.0f);

	return ball_;
}

void GameRules::start(void)
{
	//
	// Set a random direction for the ball to go. 
	Niski::Math::Random random;
	float y = static_cast<float>(random.randomNumber(0, 20));
	y = (random.randomNumber(0, 2) == 1) ? y * -1 : y;

	if(ball_)
	{
		ball_->setVelocity(Niski::Math::Vector2D<float>(-60.0f, y));
	}
	else
	{
		//
		// Throw exception or something? We could just create
		// the ball ourselves, but dunno if that is something that should ultimately be automated.
	}

	isPaused_ = false;
}

void GameRules::onScore(Niski::Math::Vector2D<float>& ballPosition)
{
	//
	// TODO we should pause the game 
	// then reset on resume..
	needReset_ = true;

	if(ballPosition.x <= world_->getBounds().left)
	{
		//
		// Give score to player 2
		//std::cout << "Player 2 scored!" << std::endl;
	}
	else
	{
		//
		// Give score to player 1
		//std::cout << "Player 1 scored!" << std::endl;
	}
}

void GameRules::think(double deltaTime)
{
	if(isPaused_)
	{
		return;
	}

	//
	// ball collision code..
	// TODO: 
	if(ball_)
	{
		Niski::Math::Vector2D<float> ballPosition(ball_->getPosition());

		if(world_)
		{
			//
			// We only care if we go out of bounds.
			Niski::Math::Rect2D worldBounds = world_->getBounds();

			if(worldBounds.isPointInRect(ballPosition) == false)
			{
				if(ballPosition.x <= worldBounds.left || ballPosition.x >= worldBounds.right)
				{
					onScore(ballPosition);
				}
				else
				{
					ball_->onTouch(world_);
				}
			}
		}
		else
		{
			Niski::Utils::warning("GameRules::think We have a ball, but no world.");
		}

		if(players_.size() > 0)
		{
			for(auto player : players_)
			{
				Paddle* paddle = player->getPaddle();

				if(paddle->getBounds().isPointInRect(ballPosition))
				{
					ball_->onTouch(paddle);
				}
			}
		}
	}
	else
	{
		Niski::Utils::warning("GameRules::think We have no ball!");
	}

	//
	// This needs to be here, after the collision check, or else the world 
	// will think a frame past the game being over.
	if(needReset_)
	{
		reset();
		start();

		if(isPaused_ == false)
		{
			pause();
		}		
	}

	if(world_)
	{
		world_->think(deltaTime);
	}
}

void GameRules::render(Niski::Renderer::Renderer& renderer) const
{
	if(world_)
	{
		world_->render(renderer);
	}
}

void GameRules::reset(void)
{
	if(players_.size() > 0)
	{
		for(auto player : players_)
		{
			player->reset();
		}
	}

	if(ball_)
	{
		ball_->reset();
	}

	needReset_ = false;

	//
	// TODO set ball_ velocity
}

void GameRules::pause(void)
{
	isPaused_ = !isPaused_;
}