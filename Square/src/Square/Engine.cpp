#include "Engine.h"

Engine& Engine::Instance()
{
	static Engine instance;
	return instance;
}

Engine::Engine()
	: mGraphics(Graphics::Instance()), mAssetManager(AssetManager::Instance()),
	mAudio(Audio::Instance()), mInputHandler(InputHandler::Instance()), 
	mTimer(Timer::Instance())
{
	mQuit = !mGraphics.Initialized();
}

Engine::~Engine()
{
	
}

void Engine::EarlyUpdate()
{
	mTimer.Update();

	mInputHandler.Update();
}

void Engine::Update()
{
	//Update game here

}

void Engine::LateUpdate()
{
	mInputHandler.UpdatePrevInput();
}

void Engine::Render()
{
	mGraphics.ClearBackBuffer();

	//Render game here
	

	mGraphics.Render();
}

void Engine::Run()
{
	while (!mQuit)
	{
		EarlyUpdate();

		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT)
				mQuit = true;
			else if (mEvent.type == SDL_KEYDOWN)
				mInputHandler.LastKey(mEvent.key.keysym.scancode);
		}

		if (mTimer.DeltaTime() >= 1.0f / FRAME_RATE)
		{
			Update();
			LateUpdate();
			Render();

			mTimer.Reset();
		}
	}
}