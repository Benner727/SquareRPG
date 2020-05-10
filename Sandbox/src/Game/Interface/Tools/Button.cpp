#include "Button.h"

Button::Button(std::string spritePath)
{
	mSprite = new Square::Sprite(spritePath);
	mSprite->Parent(this);
}

Button::~Button()
{
	delete mSprite;
}

bool Button::Pressed()
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (pos.x > mSprite->Pos().x - mSprite->ScaledDimensions().x * 0.5f &&
		pos.x < mSprite->Pos().x + mSprite->ScaledDimensions().x * 0.5f &&
		pos.y > mSprite->Pos().y - mSprite->ScaledDimensions().y * 0.5f &&
		pos.y < mSprite->Pos().y + mSprite->ScaledDimensions().y * 0.5f)
	{
		return true;
	}

	return false;
}

void Button::Update()
{
	mSprite->Update();
}

void Button::Render()
{
	mSprite->Render(true);
}
