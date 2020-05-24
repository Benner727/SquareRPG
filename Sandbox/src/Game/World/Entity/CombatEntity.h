#pragma once

#include "Game/World/Entity/MovableEntity.h"
#include "Game/World/Entity/HealthBar.h"
#include "Game/World/Entity/DamageText.h"

class CombatEntity : public MovableEntity
{
private:
	static const int COMBAT_COOLDOWN_TIME = 10;

	int mHitpoints;
	int mRemainingHitpoints;

	HealthBar mHealthBar;
	std::vector<DamageText*> mDamageText;

	bool mInCombat;
	float mCombatTimer;

	void AddDamageText(int amount);

protected:
	inline void Hitpoints(int hitpoints) { mHitpoints = hitpoints; }
	inline void RemainingHitpoints(int remainingHitpoints) { mRemainingHitpoints = remainingHitpoints; }

public:
	CombatEntity();
	virtual ~CombatEntity() = default;

	inline int Hitpoints() const { return mHitpoints; }
	inline int RemainingHitpoints() const { return mRemainingHitpoints; }

	inline bool InCombat() const { return mInCombat; }
	inline void InCombat(bool inCombat) { mInCombat = inCombat; if (inCombat) mCombatTimer = COMBAT_COOLDOWN_TIME; }

	virtual void Damage(int amount);
	virtual void Heal(int amount);

	inline bool Dead() const { return mRemainingHitpoints < 1; }

	virtual void Update();
	void RenderHealthBar();
};