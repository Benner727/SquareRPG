#pragma once

#include "Square/Core/Core.h"
#include "Square/Entities/GameObject.h"
#include "Square/Managers/AssetManager.h"

namespace Square {

	class SQUARE_API Sprite : public GameObject
	{
	protected:
		static const int FLASH_FRAMES = 6;

		std::shared_ptr<SDL_Texture> mTexture;

		Graphics& mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mRenderRect;
		SDL_Rect mClipRect;

		SDL_RendererFlip mFlip;
		SDL_Color mColor;

		bool mFlash;
		SDL_Color mFlashColor;
		int mFlashFrames;

	public:
		Sprite(const std::string& filename);
		Sprite(const std::string& filename, int x, int y, int w, int h);
		Sprite(const char& c, const std::string& fontpath, int size, SDL_Color color);
		~Sprite();

		Vector2 ScaledDimensions();

		void Flip(SDL_RendererFlip flip);
		void Color(SDL_Color color);
		SDL_Color Color();

		void FlashColor(SDL_Color color);
		void Flash();

		virtual void Render();
	};

}