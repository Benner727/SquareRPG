#pragma once

#include "Square/Core/Core.h"
#include "Square/Entities/Sprite.h"
#include "Square/Utilities/Timer.h"

namespace Square {

	class SQUARE_API AnimatedSprite : public Sprite
	{
	public:
		enum WRAP_MODE { once = 0, loop = 1 };
		enum ANIM_DIR { horizontal = 0, vertical = 1 };

	private:
		Timer& mTimer;

		int mStartX;
		int mStartY;

		float mAnimationTimer;
		float mAnimationSpeed;
		float mTimePerFrame;

		int mCurrentFrame;
		int mFrameCount;

		bool mPaused;

		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimationDirection;

		bool mAnimationDone;

	public:
		AnimatedSprite();
		AnimatedSprite(const std::string& filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDirection);
		~AnimatedSprite();

		void WrapMode(WRAP_MODE mode);

		void Play();
		void Pause();
		void Reset();

		void Frame(int frame);

		bool IsAnimating() const;

		void Update();

		AnimatedSprite& operator=(AnimatedSprite other);
		AnimatedSprite(const AnimatedSprite& other);
	};

}