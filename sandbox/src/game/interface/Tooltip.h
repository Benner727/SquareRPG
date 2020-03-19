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
	static const int TITLE_SIZE = 15;
	const SDL_Color TITLE_COLOR = { 255, 255, 255, 255 };

	Square::Text* mTitle;
	std::vector<Button*> mButtons;
	Square::Graphics& mGraphics;

	int TotalHeight();
	int MaxWidth();

	void DrawBackground();
	void DrawTitleBackground();

public:
	Tooltip(const std::string& text, std::vector<std::string> commands);
	~Tooltip();

	bool MouseOver(Square::Vector2 position);
	std::string Command();

	void Update();
	void Render();
};
