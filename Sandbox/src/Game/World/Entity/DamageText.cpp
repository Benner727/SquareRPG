#include "DamageText.h"

DamageText::DamageText(int damage)
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

DamageText::~DamageText()
{
	delete mDamageText;
}

void DamageText::Update()
{
	mLifeTimer -= Square::Timer::Instance().DeltaTime();

	Translate(Square::VEC2_UP * mSpeed * Square::Timer::Instance().DeltaTime());
	if (mOpacity > 3) mOpacity -= 3;
	mDamageText->Color({ 255, 255, 255, mOpacity });
}

void DamageText::Render()
{
	mDamageText->Render();
}