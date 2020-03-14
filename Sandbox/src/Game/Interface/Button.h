#pragma once

#include <functional>
#include <Square.h>

class Button
{
private:
	const std::string FONT_PATH = "UI/VeraMono.ttf";
	Square::Graphics& mGraphics = Square::Graphics::Instance();
	Square::Text* mText;

	std::function<void(Button*)> OnPress;

public:
	Button(std::string text, std::function<void(Button*)> func = 0);
	~Button();

	void Press();

	void Render();
};
