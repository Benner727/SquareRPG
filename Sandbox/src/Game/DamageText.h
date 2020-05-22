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
	DamageText(int damage)
	{
		mDamageText = new Square::Text(std::to_string(damage), "Font/VeraMono.ttf", 12, { 255, 255, 255, 255 });
		mDamageText->Parent(this);

		float x = 16.0f * Random::Float() - 12.0f;
		float y = -16.0f * Random::Float();

		mDamageText->Pos(Square::Vector2(x, y));

		mSpeed = 20.0f;
		mLifeTimer = 1.0f;
		mOpacity = 255;
	}

	~DamageText()
	{
		delete mDamageText;
	}

	inline bool Expired() const { return mLifeTimer <= 0.0f; }

	inline void Update()
	{
		mLifeTimer -= Square::Timer::Instance().DeltaTime();

		Translate(Square::VEC2_UP * mSpeed * Square::Timer::Instance().DeltaTime());
		if (mOpacity > 3) mOpacity -= 3;
		mDamageText->Color({ 255, 255, 255, mOpacity });
	}

	inline void Render()
	{
		mDamageText->Render();
	}
};