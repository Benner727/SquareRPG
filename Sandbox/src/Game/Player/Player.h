#pragma once

#include <Square.h>

#include "Skills.h"
#include "Game/Player/Inventory.h"
#include "Game/Player/Gear.h"

class Player : public Square::GameObject
{
private:
	Square::Sprite* mSprite;
	float mEatDelay;
	float mDrinkDelay;

	bool mInCombat;
	float mCombatDelay;

	Skills mSkills;

	Inventory mInventory;
	Gear mGear;

	void HandleDelays();

public:
	Player();
	~Player();

	inline Skills& Skills() { return mSkills; }

	inline Inventory& Inventory() { return mInventory; }
	inline Gear& Gear() { return mGear; }

	inline bool HasEatDelay() const { return (mEatDelay > 0.0f); }
	void SetEatDelay();

	inline bool HasDrinkDelay() const { return (mDrinkDelay > 0.0f); }
	void SetDrinkDelay();

	inline void InCombat(bool inCombat) { mInCombat = inCombat; }
	inline bool HasCombatDelay() const { return (mCombatDelay > 0.0f); }

	inline void ResetDelays() { mCombatDelay = mEatDelay = mDrinkDelay = 0.0f; }

	void Update();
	void Render();
};