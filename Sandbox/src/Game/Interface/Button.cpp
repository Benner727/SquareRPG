#include "Button.h"

Button::Button(std::string text, int minWidth)
 : mName(text), mInputHandler(Square::InputHandler::Instance()), mWidth(minWidth)
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
	int startX = this->Pos().x - Width() / 2;
	int endX = this->Pos().x + Width() / 2;
	int startY = this->Pos().y - Height() / 2;
	int endY = this->Pos().y + Height() / 2;

	bool hoveredX = mInputHandler.MousePos().x >= startX && mInputHandler.MousePos().x < endX;
	bool hoveredY = mInputHandler.MousePos().y >= startY && mInputHandler.MousePos().y < endY;
	return hoveredX && hoveredY;
}

bool Button::Clicked()
{
	return mInputHandler.MouseButtonPressed(Square::InputHandler::left) && MouseOver();
}

void Button::Update()
{
	if (MouseOver())
	{
		mText->Color(HOVERED_COLOR);
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
