#pragma once

#include <Square.h>

#include "Skills.h"
#include "Game/Player/Inventory.h"
#include "Game/Player/Gear.h"
#include "Game/Player/Magic/StandardSpellBook.h"
#include "Game/Player/Prayer/StandardPrayerBook.h"

class Player : public Square::GameObject
{
private:
	Square::Sprite* mSprite;

	int mCombatStance;

	float mEatDelay;
	float mDrinkDelay;

	bool mInCombat;
	float mCombatDelay;

	bool mAutoCast;

	Skills mSkills;

	Inventory mInventory;
	Gear mGear;

	StatBonus mStatBonus;

	ISpellBook* mSpellBook;
	IPrayerBook* mPrayerBook;

	void HandleDelays();

public:
	Player();
	~Player();

	inline Skills& Skills() { return mSkills; }

	inline Inventory& Inventory() { return mInventory; }
	inline Gear& Gear() { return mGear; }

	inline StatBonus& StatBonus() { return mStatBonus; }

	inline ISpellBook& SpellBook() { return *mSpellBook; }
	inline IPrayerBook& PrayerBook() { return *mPrayerBook; }

	inline int CombatStance() const { return mCombatStance; }
	inline void CombatStance(int combatStance) { mCombatStance = combatStance; }

	inline bool HasEatDelay() const { return (mEatDelay > 0.0f); }
	void SetEatDelay();

	inline bool HasDrinkDelay() const { return (mDrinkDelay > 0.0f); }
	void SetDrinkDelay();

	inline void InCombat(bool inCombat) { mInCombat = inCombat; }
	inline bool HasCombatDelay() const { return (mCombatDelay > 0.0f); }
	void SetCombatDelay();

	inline void AutoCast(bool autoCast) { mAutoCast = autoCast; }
	inline bool AutoCast() const { return mAutoCast; }

	inline void ResetDelays() { mCombatDelay = mEatDelay = mDrinkDelay = 0.0f; }

	void CalculateBonuses();

	void Update();
	void Render();
};