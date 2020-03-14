#pragma once

#include <Square.h>

class Button
{
private:
	Square::Text* mText;
	Square::Graphics& mGraphics = Square::Graphics::Instance();

	// onchange handler

public:
	Button(std::string text);
	~Button();

	void Render();
};
