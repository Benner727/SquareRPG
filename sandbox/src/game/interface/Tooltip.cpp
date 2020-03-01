#include "Tooltip.h"

Tooltip::Tooltip(const std::string text, int size, SDL_Color color) 
{
	mText = Square::Text(text, FONT_PATH, size, color);
}

Tooltip::~Tooltip()
{
}

void Tooltip::Render()
{
	mText.Render();
}
