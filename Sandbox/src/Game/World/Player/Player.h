#pragma once

#include <Square.h>
#include <list>

#include "Skills.h"
#include "Game/World/Player/Inventory.h"
#include "Game/World/Player/Gear.h"
#include "Game/World/Player/Magic/StandardSpellBook.h"
#include "Game/World/Player/Prayer/StandardPrayerBook.h"
#include "Game/World/Player/CombatStance.h"
#include "Game/World/Entity/CombatEntity.h"
#include "Game/Actions/IAction.h"

class Player : public CombatEntity, public ISubject<Player>
{
private:
	Square::Sprite* mSprite;
	Point mSpawn;

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
	Player(Point spawn);
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

	void CalculateBonuses();

	void HandleDeath();

	void Update();
	void Render();
};