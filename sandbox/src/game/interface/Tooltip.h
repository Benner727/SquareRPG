#pragma once

#include <Square.h>
#include <vector>
#include <algorithm>

#include "Game/Interface/Button.h"

class Tooltip : public Square::GameObject
{
private:
	const std::string FONT_PATH = "UI/VeraMono.ttf";
	static const int PADDING = 20;

	Square::Text* mTitle;
	std::vector<Button*> mButtons;
	Square::Graphics& mGraphics = Square::Graphics::Instance();

	void fc();
	int TotalHeight();
	int MaxWidth();
	void DrawBackground(Square::Vector2 position);
	void DrawTitleBackground();

public:
	Tooltip(const std::string text, int size = 12, SDL_Color color = { 0, 0, 0, 255 });
	~Tooltip();

	void Pos(Square::Vector2 position) { mTitle->Pos(position); };
	void Parent(Square::GameObject* parent) { mTitle->Parent(parent); }

	void Update();
	void Render();
};
