#ifndef __RENDERTHREAD_H__
#define __RENDERTHREAD_H__

#include "niski_main/ConsoleCommands.h"
#include "niski_main/Niski.h"
#include "gui/RootPanel.h"
#include "pong_game/GameRules.h"
#include "renderer/Renderer.h"

void RenderThreadFunc(shouldQuit& quit, Niski::Renderer::Renderer& renderer, Niski::Renderer::RenderWindow& win, Niski::Pong_Game::GameRules& gameRules, Niski::GUI::RootPanel& rootPanel, std::mutex& logicMutex);

#endif