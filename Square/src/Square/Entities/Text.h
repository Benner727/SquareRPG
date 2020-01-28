#pragma once

#include <vector>

#include "Square/Entities/Sprite.h"

namespace Square {

	class Text : public GameObject
	{
	private:
		std::vector<std::shared_ptr<Sprite>> mSprites;

		bool mReversed;

	public:
		Text(const std::string& text, const std::string& fontpath, int size, SDL_Color color);
		~Text();

		Vector2 ScaledDimensions();

		void Flip(SDL_RendererFlip flip);
		void Color(SDL_Color color);

		void FlashColor(SDL_Color color);
		void Flash();

		void Render();
	};

}