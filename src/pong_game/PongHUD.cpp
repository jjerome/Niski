#include "pong_game/PongHUD.h"
#include <sstream>

using namespace Niski::Pong_Game;

PongHUD::PongHUD(Niski::GUI::RootPanel* rootPanel, PongPlayer* pongPlayer, PongPlayer* pongOpponent) : Niski::GUI::Base(rootPanel, "PongHUD"), player_(pongPlayer), opponent_(pongOpponent)
{
	playerScore_ = new Niski::GUI::Label(this, "PongHUD::PlayerScore", Niski::Math::Vector2D<int32_t>(0, 0), L"Impact", 14);
	playerScore_->setText(L"Score: 0");
	playerScore_->setSize(Niski::Math::Vector2D<int32_t>(200, 100));
	playerScore_->setColor(Niski::Utils::Color(Niski::Utils::Color::white));

	opponentScore_ = new Niski::GUI::Label(this, "PongHUD::OpponentScore", Niski::Math::Vector2D<int32_t>(rootPanel->getSize().x - 100, 0), L"Impact", 14);
	opponentScore_->setText(L"Score: 0");
	opponentScore_->setSize(Niski::Math::Vector2D<int32_t>(200, 100));
	opponentScore_->setColor(Niski::Utils::Color(Niski::Utils::Color::white));

	title_ = new Niski::GUI::Label(this, "PongHUD::TitleLabel", Niski::Math::Vector2D<int32_t>((rootPanel->getSize().x / 2) - 200, 0), L"Impact", 32);
	title_->setText(L"Pong Game 2014");
	title_->setSize(Niski::Math::Vector2D<int32_t>(400, 100));
	title_->setColor(Niski::Utils::Color(Niski::Utils::Color::white));
}

PongHUD::~PongHUD(void)
{}

void PongHUD::render(Niski::Renderer::Renderer& renderer) const
{
	std::wostringstream wss;
	wss << "Score: " << player_->getScore();
	playerScore_->setText(wss.str());
	wss.str(L"");
	
	wss << "Score: " << opponent_->getScore();
	opponentScore_->setText(wss.str());
	
	playerScore_->render(renderer);
	opponentScore_->render(renderer);
	title_->render(renderer);
}