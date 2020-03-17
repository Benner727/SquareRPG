#include "Tooltip.h"

void Tooltip::DrawBackground()
{
	Square::Vector2 position = mTitle->Pos();
	int startX = position.x - MaxWidth() / 2;
	int endX = position.x + MaxWidth() / 2;
	int startY = position.y - mTitle->ScaledDimensions().y / 2 - PADDING;
	int endY = startY + TotalHeight() + PADDING;

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			bool border = x == startX || y == startY || x == endX - 1 || y == endY - 1;

			if (border)
				mGraphics.DrawPixel(Square::Vector2(x, y), { 0, 0, 0, 255 });
			else
				mGraphics.DrawPixel(Square::Vector2(x, y), { 230, 230, 230, 255 });
		}
	}
}

void Tooltip::DrawTitleBackground()
{
	int startX = mTitle->Pos().x - mTitle->ScaledDimensions().x / 2 - PADDING/2;
	int endX = mTitle->Pos().x + mTitle->ScaledDimensions().x / 2 + PADDING/2;
	int startY = mTitle->Pos().y - mTitle->ScaledDimensions().y / 2 - PADDING/2;
	int endY = mTitle->Pos().y + mTitle->ScaledDimensions().y / 2 + PADDING/2;

	for (int x = startX + 5; x < endX - 5; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			mGraphics.DrawPixel(Square::Vector2(x, y), { 0, 0, 0, 255 });
		}
	}
}

int Tooltip::TotalHeight()
{
	int height = mTitle->ScaledDimensions().y;
	if (!mButtons.empty())
		height += (mButtons.back()->Position().y - mTitle->Pos().y) + mButtons.back()->Height() / 2;

	return height;
}

int Tooltip::MaxWidth()
{
	int maxButtonWidth = 0;
	for (auto button : mButtons)
		maxButtonWidth = std::max(button->Width(), maxButtonWidth);

	return std::max((int) mTitle->ScaledDimensions().x + PADDING * 2, maxButtonWidth);
}

Tooltip::Tooltip(const std::string text, std::vector<std::string> commands)
{
	mTitle = new Square::Text(text, FONT_PATH, TITLE_SIZE, TITLE_COLOR);

	for (std::string command : commands)
	{
		Button* button = new Button(command);
		button->Parent(mTitle);
		mButtons.push_back(button);
	}
}

Tooltip::~Tooltip()
{
	for (auto button : mButtons)
		delete button;
}


bool Tooltip::MouseOver(Square::Vector2 position)
{
	Square::Vector2 titlePosition = mTitle->Pos();
	int startX = titlePosition.x - MaxWidth() / 2;
	int endX = titlePosition.x + MaxWidth() / 2;
	int startY = titlePosition.y - mTitle->ScaledDimensions().y / 2 - PADDING;
	int endY = titlePosition.y + TotalHeight() / 2 + PADDING;

	bool withinWidth = position.x >= startX && position.x < endX;
	bool withinHeight = position.y >= startY && position.y < endY;

	return withinWidth && withinHeight;
}

std::string Tooltip::Command()
{
	for (auto button : mButtons)
	{
		if (button->Clicked())
			return button->Name();
	}
	return "";
}

void Tooltip::Update()
{
	for (auto button : mButtons)
		button->Update();
}

void Tooltip::Render()
{
	DrawBackground();
	DrawTitleBackground();
	mTitle->Render();

	for (int i = 0; i < mButtons.size(); i++)
	{
		Button* button = mButtons[i];
		button->Position(Square::Vector2(0, (i+1) * 32));
		button->Render();
	}
}
