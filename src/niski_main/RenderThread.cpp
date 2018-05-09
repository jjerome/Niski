#include "niski_main/RenderThread.h"

#include "utils/Timer.h"

/*
===============================================================================

	Note that this function is temporary and is only used for testing
	out code as it is written. Ideally this would all be handled with much 
	more grace than it is currently.

===============================================================================
*/

void initializeRendererState(nativeRenderer dev)
{
	//
	// TODO: This block of code shouldn't be here, ideally. 
	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//dev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	dev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	dev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	dev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	dev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	dev->SetTextureStageState(0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE);
	dev->SetTextureStageState(0, D3DTSS_ALPHAARG2,	D3DTA_CURRENT);
	dev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	dev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
}

void RenderThreadFunc(shouldQuit& quit, Niski::Renderer::Renderer& renderer, Niski::Renderer::RenderWindow& win, Niski::Pong_Game::GameRules& gameRules, Niski::GUI::RootPanel& rootPanel, std::mutex& logicMutex)
{
	//
	// TODO: Temporary at the moment. 
	Niski::Utils::Timer timer;
	timer.start();

	double rendererAccumulator = 0.0;
	//
	// 1 second divided by 300 frames
	double maxFps = 300.0;
	double expectedFrameTime = 1.0 / maxFps;

	while(!quit.getShouldQuit())
	{
		timer.stop();

		double frameTime = timer.getTime(Niski::Utils::Timer::unit::seconds);

		/*printf("[Renderer] Frame time: %f ms\n", frameTimeMS);*/
		//
		// Avoid the frametime being so far ahead that it's impossible to catch up.
		frameTime = min(frameTime, 0.25);

		timer.reset();

		rendererAccumulator += frameTime;

		//
		// Check if we should render or wait. 
		if(rendererAccumulator >= expectedFrameTime)
		{
			//
			// TODO: Should we reset it? 
			// won't we lose the additional time accumulateD? 
			rendererAccumulator -= expectedFrameTime;

			if(!renderer.isDeviceActive())
			{
				renderer.resetDevice();
			}

			IDirect3DDevice9* dev = renderer.getNativeRenderer();
			dev->BeginScene();

			initializeRendererState(dev);

			dev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

			//
			// Lock the mutex, so data doesn't get written to 
			// while we're reading..
			logicMutex.lock();

			//
			// Render the game itself.
			gameRules.render(renderer);

			//
			// Render gui..
			rootPanel.render(renderer);

			//
			// Unlock the mutex (we're done reading).
			logicMutex.unlock();

			dev->EndScene();

			dev->Present(nullptr, nullptr, nullptr, nullptr);
		}
		// TODO: Broken! 
		else
		{
			//
			// sleep for expectedFrameTime 
			DWORD sleepTime = DWORD((expectedFrameTime - frameTime) * 1000); 

			SDL_Delay(sleepTime);
		}

		//
		// Process input/window events
		win.pollEvents();
	}
}