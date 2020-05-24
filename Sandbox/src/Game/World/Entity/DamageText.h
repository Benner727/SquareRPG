#pragma once

#include <Square.h>

#include "Random.h"

class DamageText : public Square::GameObject
{
private:
	Square::Text* mDamageText;
	float mSpeed;
	float mLifeTimer;
	Uint8 mOpacity;

public:
	DamageText(int damage);
	~DamageText();

	inline bool Expired() const { return mLifeTimer <= 0.0f; }

	void Update();
	void Render();
};