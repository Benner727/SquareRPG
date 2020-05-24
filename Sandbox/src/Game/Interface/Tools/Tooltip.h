#pragma once

#include <Square.h>

#include <vector>

class Tooltip : public Square::GameObject
{
private:
	static const std::string FONT_PATH;
	static const int PADDING = 4;

	Square::Vector2 mTopLeft;
	int mWidth;
	int mHeight;

	std::vector<Square::Text*> mInfoText;

public:
	Tooltip(std::vector<std::string> info, Square::Vector2 pos);
	~Tooltip();

	void Update();
	void Render();
};