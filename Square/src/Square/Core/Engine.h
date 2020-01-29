#pragma once

#include "Square/Core/Core.h"
#include "Square/Managers/Audio.h";
#include "Square/Managers/InputHandler.h"
#include "Square/Utilities/Timer.h"
#include "Square/Core/Layer.h"

#include <vector>

namespace Square {

	class SQUARE_API Engine
	{
	private:
		const int FRAME_RATE = 60;

		bool mQuit;

		Graphics& mGraphics;
		AssetManager& mAssetManager;
		Audio& mAudio;
		InputHandler& mInputHandler;

		Timer& mTimer;

		std::vector<Layer*> mLayerStack;

		SDL_Event mEvent;

		Engine();
		~Engine();

		void EarlyUpdate();
		void Update();
		void LateUpdate();

		void Render();

	public:
		static Engine& Instance();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void Run();
	};

}