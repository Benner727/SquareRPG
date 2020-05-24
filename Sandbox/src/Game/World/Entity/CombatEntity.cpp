#include "CombatEntity.h"

CombatEntity::CombatEntity()
{
	mHitpoints = 1;
	mRemainingHitpoints = 1;

	mInCombat = false;
	mCombatTimer = 0.0f;
}

void CombatEntity::AddDamageText(int amount)
{
	mDamageText.push_back(new DamageText(amount));
	mDamageText.back()->Parent(this);
	mDamageText.back()->Pos(Square::VEC2_ZERO);
}

void CombatEntity::Damage(int amount)
{
	mRemainingHitpoints -= amount;
	if (mRemainingHitpoints < 0)
		mRemainingHitpoints = 0;
	
	AddDamageText(amount);
}

void CombatEntity::Heal(int amount)
{
	mRemainingHitpoints += amount;
	if (mRemainingHitpoints > mHitpoints)
		mRemainingHitpoints = mHitpoints;
}

void CombatEntity::Update()
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

void CombatEntity::RenderHealthBar()
{
	if (InCombat() && mCombatTimer >= 5.0f) mHealthBar.Render();

	for (auto damageText : mDamageText)
		damageText->Render();
}