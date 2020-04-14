#pragma once

#include <Square.h>

class Button : public Square::GameObject
{
private:
	Square::Sprite* mSprite;

public:
	Button(std::string spritePath);
	~Button();

	inline int Width() const { return mSprite->ScaledDimensions().x; }
	inline int Height() const { return mSprite->ScaledDimensions().y; }

	bool Pressed();

	virtual void Update();
	virtual void Render();
};