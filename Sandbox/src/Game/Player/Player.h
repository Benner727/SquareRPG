#pragma once

#include "Square.h"

#include "Game/Player/Inventory.h"

class Player : public Square::GameObject
{
private:
	Square::Sprite* mSprite;
	float mEatDelay;
	float mDrinkDelay;

	bool mInCombat;
	float mCombatDelay;

	Inventory mInventory;

	void HandleDelays();

public:
	Player();
	~Player();

	inline Inventory& Inventory() { return mInventory; }

	inline bool HasEatDelay() const { return (mEatDelay > 0.0f); }
	void SetEatDelay();
	void Heal(int amount);

	inline bool HasDrinkDelay() const { return (mDrinkDelay > 0.0f); }
	void SetDrinkDelay();

	inline void InCombat(bool inCombat) { mInCombat = inCombat; }
	inline bool HasCombatDelay() const { return (mCombatDelay > 0.0f); }

	inline void ResetDelays() { mCombatDelay = mEatDelay = mDrinkDelay = 0.0f; }

	void Update();
	void Render();
};