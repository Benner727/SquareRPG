#pragma once

#include <Square.h>
#include <list>

#include "Skills.h"
#include "Game/Player/Inventory.h"
#include "Game/Player/Gear.h"
#include "Game/Player/Magic/StandardSpellBook.h"
#include "Game/Player/Prayer/StandardPrayerBook.h"
#include "Game/Player/CombatStance.h"
#include "Game/CombatEntity.h"
#include "Game/Actions/IAction.h"

class Player : public CombatEntity
{
private:
	Square::Sprite* mSprite;

	CombatStance mCombatStance;

	std::shared_ptr<Square::GameObject> mTarget;

	IAction* mAction;

	float mEatDelay;
	float mDrinkDelay;

	bool mInCombat;
	float mCombatTimer;
	float mCombatDelay;

	Skills mSkills;

	Inventory mInventory;
	Gear mGear;

	StatBonus mStatBonus;

	ISpellBook* mSpellBook;
	IPrayerBook* mPrayerBook;

	void HandleDelays();
	void HandlePrayer();

	void CombatUpdate();

public:
	Player();
	~Player();

	inline Skills& Skills() { return mSkills; }

	inline Inventory& Inventory() { return mInventory; }
	inline Gear& Gear() { return mGear; }

	inline StatBonus& StatBonus() { return mStatBonus; }

	inline ISpellBook& SpellBook() { return *mSpellBook; }
	inline IPrayerBook& PrayerBook() { return *mPrayerBook; }

	void SetAction(IAction* action);

	inline CombatStance& GetCombatStance() { return mCombatStance; }

	inline void Damage(int amount) override { CombatEntity::Damage(amount); mSkills.TakeDamage(amount); }
	inline void Heal(int amount) override { CombatEntity::Heal(amount); mSkills.Heal(amount); }

	inline void Target(std::shared_ptr<Square::GameObject> target) { mTarget = target; }
	inline std::shared_ptr<Square::GameObject> Target() const { return mTarget; }

	inline bool HasEatDelay() const { return (mEatDelay > 0.0f); }
	void SetEatDelay();

	inline bool HasDrinkDelay() const { return (mDrinkDelay > 0.0f); }
	void SetDrinkDelay();

	inline bool HasCombatDelay() const { return (mCombatDelay > 0.0f); }
	void SetCombatDelay();

	inline void ResetDelays() { mCombatDelay = mEatDelay = mDrinkDelay = 0.0f; }

	void CalculateBonuses();

	void Update();
	void Render();
};