#pragma once

#include <Square.h>

#include <vector>
#include <iterator>

class MessageLog : public Square::GameObject
{
private:
	Square::Sprite* mBackground;
	std::vector<Square::Text*> mText;
	int mWidth;
	int mHeight;
	std::string mFontPath;
	int mFontSize;

	void AddMessage(Square::Text* message);

public:
	MessageLog(int width, int height, std::string fontPath, int fontSize, Square::Vector2 offset = Square::VEC2_ZERO);
	~MessageLog();

	bool ContainsClick() const;

	void AddMessage(std::string text, SDL_Color color);

	void Render();
};