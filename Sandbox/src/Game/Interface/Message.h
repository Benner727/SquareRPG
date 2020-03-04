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

	void AddMessage(Square::Text* message);

public:
	MessageLog(int width, int height);
	~MessageLog();

	void AddMessage(std::string text, SDL_Color color);

	void Render();
};