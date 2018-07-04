// Niski.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS 1

#include "niski_main/Niski.h"

#include <sstream>
#include <thread>
#include <chrono>

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "SDL/SDL.h"

#include "gui/Console.h"
#include "gui/RootPanel.h"
#include "gui/TextInput.h"
#include "input/InputSystem.h"
#include "math/Vec2d.h"
#include "pong_game/GameRules.h"
#include "pong_game/PongHUD.h"
#include "renderer/RenderWindow.h"
#include "renderer/Renderer.h"
#include "utils/Assert.h"
#include "utils/Debug.h"
#include "utils/win32/AssertCallBack.h"
#include "utils/win32/System.h"
#include "utils/win32/Win32Includes.h"
#include "utils/DataDirectory.h"
#include "utils/Timer.h"

#include "niski_main/ConsoleCommands.h"
#include "niski_main/GameLogicThread.h"
#include "niski_main/RenderThread.h"

int NiskiEventFilter(void* userData, SDL_Event* evt)
{
	if (evt->type == SDL_QUIT)
	{
		shouldQuit* q = reinterpret_cast<shouldQuit*>(userData);
		//
		// setShouldQuit is, in theory, anyways, thread safe. 
		q->setShouldQuit(true);
	}

	return 0;
}

#ifndef _WIN32
int main(int argc, const char* argv[])
#else
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
#ifdef _WIN32
	//
	// Thanks to https://bobobobo.wordpress.com/2009/03/01/how-to-attach-a-console-to-your-gui-app-in-c/
	// FIXME: PURELY FOR TESTING.
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif


	//
	// Set up our writable directory for configs / etc. 
	Niski::Utils::DataDirectory::openDataDirectory("Pong_Game");
	//
	// Install the win32 assert callback. 
	Niski::Utils::Assert::installAssertCallBack(Niski::Utils::Win32::win32AssertCallBack);

	//
	// Initialize our quit system (hacky)
	// and some console commands 
	shouldQuit quit;
	QuitCmd quitCmd(&quit);
	TestCmd testCmd;
	EchoCmd echoCmd;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL. SDL returned: %s\n", SDL_GetError());
		return 1;
	}

	//
	// Initialize our input system and the key bind system.
	Niski::Input::InputSystem inputSystem;
	Niski::Engine::KeyBindings keyBinds;
	inputSystem.addInputListener(&keyBinds);

	//
	// Install our event filter. 
	SDL_AddEventWatch(&NiskiEventFilter, &quit);

	//
	// Initialize the render window and the renderer..
	std::ostringstream winTitle;

	winTitle << "Niski Engine Test" << ((_DEBUG) ? " // DEBUG // " : " \\\\ RETAIL \\\\ ") << "(Build Date: " << __DATE__  << ")";

	Niski::Renderer::RenderWindow win(winTitle.str(), Niski::Math::Rect2D(100, 100, 720, 1280), &inputSystem, Niski::Renderer::RenderWindow::hasBorder);
	Niski::Renderer::Renderer renderer(win, Niski::Math::Vector2D<int32_t>(1280, 720), Niski::Renderer::Renderer::windowed); //win.getDimensions().right, win.getDimensions().bottom), Niski::Renderer::Renderer::windowed);

	//
	// Initialize some Pong_Game stuff (game rules - this allows us to make our paddles and the ball)
	Niski::Pong_Game::GameRules gameRules;
	
	keyBinds.setBinding(Niski::Input::Key_Escape, "Engine::Quit");
	keyBinds.setBinding(Niski::Input::Key_F1, "PongGame::GameRules::Reset");
	keyBinds.setBinding(Niski::Input::Key_F2, "PongGame::GameRules::Pause");
	keyBinds.setBinding(Niski::Input::Mouse_Side_Forward, "Engine::Test");
	keyBinds.setBinding(Niski::Input::Key_F3, "Engine::Echo arg1 arg2 \"arg3 arg3 arg3\" arg4");

	//
	// Initialize our GUI stuff - you only need to really initialize
	// the root panel... you can initialize other stuff off the root 
	// panel later on and it will handle all of that.
	Niski::Math::Vector2D<int32_t> position(0,0);
	Niski::GUI::RootPanel rootPanel;
	rootPanel.setBounds(Niski::Math::Rect2D(0, 0, 720, 1280));
	rootPanel.setPadding(Niski::Math::Rect2D(10, 10, 10, 10));

	Niski::GUI::Console devConsole(&rootPanel);
	devConsole.addLine("Hello world!", Niski::Utils::Color::red);
	devConsole.addLine("Hello world!", Niski::Utils::Color::white);
	devConsole.addLine("Hello world!", Niski::Utils::Color::black);
	devConsole.addLine("Hello world!", Niski::Utils::Color::green);

	//
	// Initialize game entities.
	gameRules.createGameWorld(Niski::Math::Rect2D(0, 0, 720, 1280));
	auto bot = gameRules.createBot(0.0f + 25.0f);
	auto bot2 = gameRules.createBot(1280.0f - 25.0f);
	auto ball = gameRules.createBall();

	Niski::Pong_Game::PongHUD pongHUD(&rootPanel, bot, bot2);

	Niski::GUI::TextInput textInput(&rootPanel, "textInputTest", Niski::Math::Vector2D<int32_t>(720 / 2, 1280 / 2), Niski::GUI::FontCfg("Arial", 12));

	inputSystem.addInputListener(&rootPanel);
	inputSystem.addMouseListener(&rootPanel);
	inputSystem.setCharListener(&rootPanel);

	//
	// Precache everything - specifically GUI::Label
	// needs this so we can do the sizeToContents method
	// but other widgets may need it in the future
	rootPanel.precache(renderer);

	//
	// Ask the rootpanel to perform the layout..
	// I dunno if this will be required later on
	// but this just lays out the children so they're not
	// clipping etc.
	rootPanel.performLayout();

	//
	// Run our game logic in its own thread
	// so we can render in this one (which is also reading the message pump).
	std::mutex logicMutex;
	std::thread gameLogic(gameLogicThreadFunc, std::ref(quit), std::ref(gameRules), std::ref(rootPanel), std::ref(logicMutex));
	RenderThreadFunc(quit, renderer, win, gameRules, rootPanel, logicMutex);

	//
	// Once we reach this, the quit class has told us to quit
	// and thus the thread should join ours and we exit out.
	gameLogic.join();

	SDL_Quit();

	return 0;
}