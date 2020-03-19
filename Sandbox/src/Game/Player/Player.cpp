#include "Game/Player/Player.h"

Player::Player()
{
	mSprite = new Square::Sprite("Player.png");
	mSprite->Parent(this);

	mSpellBook = new StandardSpellBook();
	mPrayerBook = new StandardPrayerBook();

	mCombatStance = CombatOption::melee_accurate;
	mTarget = nullptr;

	mEatDelay = 0.0f;
	mDrinkDelay = 0.0f;

	mInCombat = false;
	mCombatDelay = 0.0f;

	mTarget = nullptr;

	mMoving = false;
	mMoveSpeed = 64.0f;
	mMapPosition = { 0, 0, 0 };
	Pos(Square::Vector2(16.0, 16.0));
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
	else
		mEatDelay = 0.6f;
}

void Player::SetDrinkDelay()
{
	if (mInCombat)
	{
		mCombatDelay += 1.8f - mEatDelay;
		mDrinkDelay = 1.8f;
	}
	else
		mDrinkDelay = 0.6f;
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

void Player::HandlePrayer()
{
	static float prayerDrain = 0.0f;
	
	if (mSkills.EffectiveLevel(Skills::SkillIndex::prayer) > 0)
	{
		prayerDrain += mPrayerBook->PrayerDrain()
			* (1.0f - ((float)mStatBonus.Bonus(StatBonus::Prayer) / 61.0f))
			* Square::Timer::Instance().DeltaTime();

		if (prayerDrain >= 1.0f)
		{
			mSkills.DrainSkill(Skills::SkillIndex::prayer, (int)prayerDrain);
			prayerDrain -= (int)prayerDrain;
		}

		if (mSkills.EffectiveLevel(Skills::SkillIndex::prayer) < 1)
			mPrayerBook->ToggleAllOff();
	}
}

void Player::HandleMovement()
{
	if (mMoving)
	{
		Square::Vector2 endPosition = Square::Vector2(mMapPosition.x * 32 + 16, mMapPosition.y * 32 + 16);

		if ((Pos() - endPosition).Magnitude() > 1.0f)
		{
			Square::Vector2 direction = (endPosition - Pos()).Normalize();
			float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;
			Translate(Square::RotateVector(mMoveSpeed * Square::Timer::Instance().DeltaTime(), angle));
		}
		else
		{
			Pos(endPosition);
			mMoving = false;
		}
	}
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

void Player::MoveTo(Point point)
{
	mMoving = true;
	mMapPosition = point;
}

void Player::Update()
{
	HandleDelays();

	mSkills.Update();

	HandlePrayer();

	HandleMovement();

	Square::Graphics::Instance().Camera(Pos());
}

void Player::Render()
{
	mSprite->Render();
}