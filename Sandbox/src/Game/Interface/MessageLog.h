#pragma once

#include <Square/Entities/Text.h>

#include <vector>
#include <iterator>

class MessageLog : public Square::GameObject
{
private:
	std::vector<Square::Text*> mText;
	int mWidth;
	int mHeight;
	std::string mFontPath;
	int mFontSize;

	void AddMessage(Square::Text* message);

public:
	MessageLog(int width, int height, std::string fontPath, int fontSize);
	~MessageLog();

	void AddMessage(std::string text, SDL_Color color);

	void Render();
};