#ifndef ENGINE_H
#define ENGINE_H

#include "Audio.h";
#include "InputHandler.h"
#include "Timer.h"

class Engine
{
private:
	const int FRAME_RATE = 60;

	bool mQuit;

	Graphics& mGraphics;
	AssetManager& mAssetManager;
	Audio& mAudio;
	InputHandler& mInputHandler;

	Timer& mTimer;

	SDL_Event mEvent;

	Engine();
	~Engine();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

public:
	static Engine& Instance();

	void Run();
};

#endif