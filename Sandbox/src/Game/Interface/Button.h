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
	std::string mName;
	Square::Text* mText;
	Square::InputHandler& mInputHandler;

	bool MouseOver();

public:
	Button(std::string& text, int minWidth = 0);
	~Button();

	inline std::string Name() const { return mName; }
	inline int Height() const { return mText->ScaledDimensions().y + VERTICAL_PADDING * 2; }
	inline int Width() const { return std::max((int) mText->ScaledDimensions().x, mWidth); }

	bool Clicked();

	void Update();
	void Render();
};
