#include "Button.h"

Button::Button(std::string text, std::function<void()> func, int minWidth)
	: OnPress(func), mInputHandler(Square::InputHandler::Instance()), mWidth(minWidth)
{
	mText = new Square::Text(text, FONT_PATH, SIZE, COLOR);
	mText->Parent(this);
}

Button::~Button()
{
	delete mText;
}

bool Button::MouseOver()
{
	int startX = mText->Pos().x - Width() / 2;
	int endX = mText->Pos().x + Width() / 2;
	int startY = mText->Pos().y - Height() / 2;
	int endY = mText->Pos().y + Height() / 2;

	bool hoveredX = mInputHandler.MousePos().x >= startX && mInputHandler.MousePos().x < endX;
	bool hoveredY = mInputHandler.MousePos().y >= startY && mInputHandler.MousePos().y < endY;
	return hoveredX && hoveredY;
}

void Button::HandleClick()
{
	if (mInputHandler.MouseButtonPressed(Square::InputHandler::left))
		Press();
}

void Button::Position(Square::Vector2 pos)
{
	this->Pos(pos);
}

void Button::Press()
{
	if (OnPress)
		OnPress();
}

void Button::Update()
{
	if (MouseOver())
	{
		mText->Color(HOVERED_COLOR);
		HandleClick();
	}
	else
	{
		mText->Color(COLOR);
	}
}

void Button::Render()
{
	if (mText)
		mText->Render();
}
