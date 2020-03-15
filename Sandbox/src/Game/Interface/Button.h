#pragma once

#include <functional>
#include <algorithm>
#include <Square.h>

class Button : public Square::GameObject
{
private:
	const std::string FONT_PATH = "UI/VeraMono.ttf";
	const SDL_Color COLOR = { 0, 0, 0, 255 };
	const SDL_Color HOVERED_COLOR = { 150, 150, 150, 255 };
	static const int SIZE = 12;
	static const int VERTICAL_PADDING = 10;
	Square::Graphics& mGraphics = Square::Graphics::Instance();

	int mWidth;
	Square::Text* mText;
	std::function<void()> OnPress;

	Square::InputHandler& mInputHandler;

	bool MouseOver();
	void HandleClick();

public:
	Button(std::string text, std::function<void()> func = 0, int minWidth = 0);
	~Button();

	inline int Height() const { return mText->ScaledDimensions().y + VERTICAL_PADDING * 2; }
	inline int Width() const { return std::max((int) mText->ScaledDimensions().x, mWidth); }

	void Position(Square::Vector2 pos);
	void Press();
	void Update();
	void Render();
};
