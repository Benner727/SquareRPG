#include "Game/Player/Player.h"

Player::Player()
{
	mSprite = nullptr;
	//mSprite->Parent(this);

	mSpellBook = new StandardSpellBook();
	mPrayerBook = new StandardPrayerBook();

	mCombatStance = 1;

	mEatDelay = 0.0f;
	mDrinkDelay = 0.0f;

	mInCombat = false;
	mCombatDelay = 0.0f;

	mAutoCast = false;
}

Player::~Player()
{
	delete mSprite;

	delete mSpellBook;
	delete mPrayerBook;

}

void Player::SetEatDelay()
{
	if (mInCombat)
	{
		mCombatDelay += 1.8f - mDrinkDelay;
		mEatDelay = 1.8f;
	}
}

void Player::SetDrinkDelay()
{
	if (mInCombat)
	{
		mCombatDelay += 1.8f - mEatDelay;
		mDrinkDelay = 1.8f;
	}
}

void Player::SetCombatDelay()
{
	if (Weapon* weapon = dynamic_cast<Weapon*>(mGear.GetItem(Gear::EquipmentSlot::weapon)))
		mCombatDelay += weapon->Speed();
	else
		mCombatDelay += 2.4f;
}

void Player::HandleDelays()
{
	if (mEatDelay > 0.0f)
		mEatDelay -= Square::Timer::Instance().DeltaTime();

	if (mDrinkDelay > 0.0f)
		mDrinkDelay -= Square::Timer::Instance().DeltaTime();

	if (mCombatDelay > 0.0f)
		mCombatDelay -= Square::Timer::Instance().DeltaTime();
}

void Player::CalculateBonuses()
{
	mStatBonus.Reset();

	for (int i = 0; i < Gear::GEAR_SIZE; i++)
	{
		if (Equipment* equipment = dynamic_cast<Equipment*>(mGear.GetItem(i)))
		{
			mStatBonus += equipment->Bonuses();
		}
	}
}

void Player::Update()
{
	HandleDelays();

	mSkills.Update();
}

void Player::Render()
{
	mSprite->Render();
}