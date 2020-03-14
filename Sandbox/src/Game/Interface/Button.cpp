#include "Button.h"

Button::Button(std::string text, std::function<void(Button*)> func)
	: OnPress(func)
{
	mText = new Square::Text(text, FONT_PATH, 15, { 255, 255, 255 });
}

Button::~Button()
{
	delete mText;
}

void Button::Press()
{
	if (OnPress)
		OnPress(this);
}

void Button::Render()
{
}
