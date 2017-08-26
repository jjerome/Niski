#ifndef __PONG_GAME_PONGHUD_H__
#define __PONG_GAME_PONGHUD_H__

#include "gui/Base.h"
#include "gui/Label.h"
#include "gui/RootPanel.h"

#include "pong_game/PongPlayer.h"

namespace Niski
{
	namespace Pong_Game
	{
		//
		// TODO: Have a base HUD class, perhaps. Only difference should be ignoring all input, completely. 
		class PongHUD : Niski::GUI::Base
		{
		public:
			PongHUD(Niski::GUI::RootPanel* rootPanel, PongPlayer* pongPlayer, PongPlayer* pongOpponent);
			~PongHUD(void);

			void render(Niski::Renderer::Renderer& renderer) const;

		private:
			PongPlayer* player_;
			PongPlayer* opponent_;
			Niski::GUI::Label* playerScore_;
			Niski::GUI::Label* opponentScore_;
			Niski::GUI::Label* title_;
			Niski::GUI::Label* timer_;
		};
	}
}

#endif