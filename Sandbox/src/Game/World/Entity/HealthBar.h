#pragma once

#include <Square.h>

class HealthBar : public Square::GameObject
{
private:
	int mLastRemainingHitpoints;
	int mLastHitpoints;

	std::vector<Square::Sprite*> mHealthBar;

public:
	HealthBar();
	~HealthBar();

	void Update(int remainingHitpoints, int hitpoints);
	void Render();
};