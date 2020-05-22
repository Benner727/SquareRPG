#pragma once

#include "Game/MovableEntity.h"
#include "Game/HealthBar.h"
#include "Game/DamageText.h"

class CombatEntity : public MovableEntity
{
private:
	int mHitpoints;
	int mRemainingHitpoints;

	HealthBar mHealthBar;
	std::vector<DamageText*> mDamageText;

	bool mInCombat;
	float mCombatTimer;

	void AddDamageText(int amount)
	{
		mDamageText.push_back(new DamageText(amount));
		mDamageText.back()->Parent(this);
		mDamageText.back()->Pos(Square::VEC2_ZERO);
	}

protected:
	void Hitpoints(int hitpoints) { mHitpoints = hitpoints; }
	void RemainingHitpoints(int remainingHitpoints) { mRemainingHitpoints = remainingHitpoints; }

public:
	CombatEntity() 
	{
		mHitpoints = 1;
		mRemainingHitpoints = 1;

		mInCombat = false;
		mCombatTimer = 0.0f;
	}

	virtual ~CombatEntity() = default;

	inline int Hitpoints() const { return mHitpoints; }
	inline int RemainingHitpoints() const { return mRemainingHitpoints; }

	inline bool InCombat() const { return mInCombat; }
	inline void InCombat(bool inCombat) { mInCombat = inCombat; if (inCombat) mCombatTimer = 10.0f; }

	inline virtual void Damage(int amount) { mRemainingHitpoints -= amount; if (mRemainingHitpoints < 0) mRemainingHitpoints = 0; AddDamageText(amount); }
	inline virtual void Heal(int amount) { mRemainingHitpoints += amount; if (mRemainingHitpoints > mHitpoints) mRemainingHitpoints = mHitpoints; }

	inline bool Dead() const { return mRemainingHitpoints < 1; }

	inline void Update()
	{
		if (mInCombat)
		{
			mCombatTimer -= Square::Timer::Instance().DeltaTime();
			mInCombat = (mCombatTimer > 0.0f);

			mHealthBar.Pos(Pos());
			mHealthBar.Update(RemainingHitpoints(), Hitpoints());
		}

		for (std::vector<DamageText*>::iterator it = mDamageText.begin(); it != mDamageText.end();)
		{
			(*it)->Update();
			if ((*it)->Expired())
				it = mDamageText.erase(it);
			else
				++it;
		}
	}

	inline void RenderHealthBar()
	{
		if (InCombat()) mHealthBar.Render();
		
		for (auto damageText : mDamageText)
			damageText->Render();
	}
};