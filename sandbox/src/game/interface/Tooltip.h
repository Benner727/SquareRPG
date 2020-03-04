#pragma once

#include <Square.h>

class Tooltip
{
private:
	const std::string FONT_PATH = "Symbola_hint.ttf";

	Square::Text* mText;

public:
	Tooltip(const std::string text, int size = 12, SDL_Color color = { 255, 255, 255, 255 });
	~Tooltip();

	void Pos(Square::Vector2 position) { mText->Pos(position); };
	void Parent(Square::GameObject* parent) { mText->Parent(parent); }

	void Render();
};

