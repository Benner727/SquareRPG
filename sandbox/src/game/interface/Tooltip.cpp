#include "Tooltip.h"

Tooltip::Tooltip(const std::string& text, std::vector<std::string> commands)
	:mGraphics(Square::Graphics::Instance())
{
	mTitle = new Square::Text(text, FONT_PATH, TITLE_SIZE, TITLE_COLOR);
	mTitle->Parent(this);

	for (std::string command : commands)
	{
		Button* button = new Button(command);
		button->Parent(this);
		mButtons.push_back(button);
	}
}

Tooltip::~Tooltip()
{
	for (auto button : mButtons)
		delete button;
}

void Tooltip::DrawBackground()
{
	Square::Vector2 position = mTitle->Pos();
	int x = position.x - MaxWidth() / 2;
	int y = position.y - mTitle->ScaledDimensions().y / 2 - PADDING;
	int width = MaxWidth();
	int height = TotalHeight() + PADDING;

	mGraphics.DrawRectangle(Square::Vector2(x, y), width, height, { 230, 230, 230, 255 });
}

void Tooltip::DrawTitleBackground()
{
	int x = mTitle->Pos().x - mTitle->ScaledDimensions().x / 2 - PADDING/2;
	int y = mTitle->Pos().y - mTitle->ScaledDimensions().y / 2 - PADDING/2;
	int width = mTitle->ScaledDimensions().x + PADDING;
	int height = mTitle->ScaledDimensions().y + PADDING;

	mGraphics.DrawRectangle(Square::Vector2(x, y), width, height, { 0, 0, 0, 255 });
}

int Tooltip::TotalHeight()
{
	int height = mTitle->ScaledDimensions().y;
	if (!mButtons.empty())
		height += (mButtons.back()->Pos().y - mTitle->Pos().y) + mButtons.back()->Height() / 2;

	return height;
}

int Tooltip::MaxWidth()
{
	int maxButtonWidth = 0;
	for (auto button : mButtons)
		maxButtonWidth = std::max(button->Width(), maxButtonWidth);

	return std::max((int) mTitle->ScaledDimensions().x + PADDING * 2, maxButtonWidth);
}

bool Tooltip::MouseOver(Square::Vector2 position)
{
	Square::Vector2 titlePosition = mTitle->Pos();
	int startX = titlePosition.x - MaxWidth() / 2;
	int startY = titlePosition.y - mTitle->ScaledDimensions().y / 2 - PADDING;
	int endX = startX + MaxWidth();
	int endY = startY + TotalHeight() + PADDING;

	bool withinWidth = position.x >= startX && position.x < endX;
	bool withinHeight = position.y >= startY && position.y < endY;

	return withinWidth && withinHeight;
}

std::string Tooltip::Command()
{
	std::string command = "";
	for (auto button : mButtons)
	{
		if (button->Clicked())
		{
			command = button->Name();
			break;
		}
	}
	return command;
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
		mButtons[i]->Pos(Square::Vector2(0, (i+1) * 32));
		mButtons[i]->Render();
	}
}
