#pragma once

#include <Square.h>
#include <vector>

#include "Game/Interface/Button.h"

class Tooltip
{
private:
	const std::string FONT_PATH = "UI/VeraMono.ttf";
	static const int PADDING = 20;

	Square::Text* mTitle;
	std::vector<Button> mButtons;
	Square::Graphics& mGraphics = Square::Graphics::Instance();

	void DrawBackground(Square::Vector2 position);

public:
	Tooltip(const std::string text, int size = 12, SDL_Color color = { 255, 255, 255, 255 });
	~Tooltip();

	void Pos(Square::Vector2 position) { mText->Pos(position); };
	void Parent(Square::GameObject* parent) { mText->Parent(parent); }

	void Render();
};
