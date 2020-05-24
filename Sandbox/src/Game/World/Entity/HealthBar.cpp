#include "HealthBar.h"

HealthBar::HealthBar()
{
	mLastRemainingHitpoints = 0;
	mLastHitpoints = 0;
}

HealthBar::~HealthBar()
{
	for (auto healthBar : mHealthBar)
		delete healthBar;
}

void HealthBar::Update(int remainingHitpoints, int hitpoints)
{
	if (mLastRemainingHitpoints != remainingHitpoints ||
		mLastHitpoints != hitpoints)
	{
		for (auto healthBar : mHealthBar)
			delete healthBar;
		mHealthBar.clear();

		int newSize = 24.0f * ((float)remainingHitpoints / hitpoints);
		float y = Pos().y - 20.0f;

		for (int i = 0; i < 24; i++)
		{
			if (i < newSize)
			{
				mHealthBar.push_back(new Square::Sprite("Healthbar.png", 0, 0, 1, 5));
				mHealthBar.back()->Pos(Square::Vector2((Pos().x - 12) + 1.0f * i, y));
				mHealthBar.back()->Parent(this);
			}
			else
			{
				mHealthBar.push_back(new Square::Sprite("Healthbar.png", 1, 0, 1, 5));
				mHealthBar.back()->Pos(Square::Vector2((Pos().x - 12) + 1.0f * i, y));
				mHealthBar.back()->Parent(this);
			}
		}
	}

	mLastRemainingHitpoints = remainingHitpoints;
	mLastHitpoints = hitpoints;
}

void HealthBar::Render()
{
	for (const auto& healthBar : mHealthBar)
		healthBar->Render();
}