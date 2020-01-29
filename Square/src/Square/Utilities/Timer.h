#pragma once

#include <SDL2/SDL.h>

#include "Square/Core/Core.h"

namespace Square {

	class SQUARE_API Timer
	{
	private:
		Uint32 mStartTicks;
		Uint32 mEndTicks;

		float mDeltaTime;

		Timer();
		~Timer();

	public:
		static Timer& Instance();

		float DeltaTime();

		void Update();
		void Reset();
	};

}