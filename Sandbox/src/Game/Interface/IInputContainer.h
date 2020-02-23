#pragma once

#include <Square.h>

class IInputContainer : public Square::GameObject
{
private:
	static const Square::Vector2 mPosition;
	std::vector<Square::Sprite> mInputs;
	int mActiveSlot;

public:
};

