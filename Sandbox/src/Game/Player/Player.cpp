#include "Game/Player/Player.h"

Player::Player()
{
	mSprite = nullptr;
	//mSprite->Parent(this);

	mEatDelay = 0.0f;
	mDrinkDelay = 0.0f;

	mInCombat = false;
	mCombatDelay = 0.0f;
}

Player::~Player()
{
	delete mSprite;

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