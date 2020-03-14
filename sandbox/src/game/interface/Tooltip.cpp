#include "Tooltip.h"

void Tooltip::DrawBackground(Square::Vector2 position)
{
	Square::Vector2 dimensions = mTitle->ScaledDimensions();
	int startX = position.x - dimensions.x / 2 - PADDING;
	int endX = position.x + dimensions.x / 2 + PADDING;
	int startY = position.y - dimensions.y / 2 - PADDING;
	int endY = position.y + dimensions.y / 2 + PADDING;
	
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			mGraphics.DrawPixel(Square::Vector2(x, y), { 255, 255, 255, 100 });
		}
	}
}

Tooltip::Tooltip(const std::string text, int size, SDL_Color color)
{
	mTitle = new Square::Text(text, FONT_PATH, size, color);
	std::cout << mTitle->ScaledDimensions().x << ", " << mTitle->ScaledDimensions().y << std::endl;
}

Tooltip::~Tooltip()
{
}

void Tooltip::Render()
{
	DrawBackground(mTitle->Pos());
	mTitle->Render();
}
