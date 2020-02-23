#pragma once

#include <Square.h>

class Button : public Square::GameObject
{
private:
	std::string mText;

public:
	Button();
	~Button();
};
