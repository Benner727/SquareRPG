#include "Player.h"

Player::Player()
	: Player(Point(0, 0))
{
}

Player::Player(Point spawn)
	: mSpawn(spawn)
{
	mSprite = new Square::Sprite("Player.png");
	mSprite->Parent(this);

	mSpellBook = new StandardSpellBook();
	mPrayerBook = new StandardPrayerBook();

	mTarget = nullptr;

	mEatDelay = 0.0f;
	mDrinkDelay = 0.0f;

	mInCombat = false;
	mCombatTimer = 0.0f;
	mCombatDelay = 0.0f;

	mAction = nullptr;

	Pos(Square::Vector2(16.0, 16.0));
	MapPosition(mSpawn);
}

Player::~Player()
{
	delete mSprite;

	delete mSpellBook;
	delete mPrayerBook;

	delete mAction;
}

void Player::SetAction(IAction* action)
{
	delete mAction;
	mAction = action;
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
		//mCombatDelay += 1.8f - mEatDelay;
		mDrinkDelay = 1.8f;
	}
	else
		mDrinkDelay = 0.6f;
}

void Player::SetCombatDelay()
{
	if (Weapon* weapon = dynamic_cast<Weapon*>(mGear.GetItem(Gear::EquipmentSlot::weapon).get()))
	{
		if (GetCombatStance().Get() == CombatOption::magic_standard || GetCombatStance().Get() == CombatOption::magic_defensive)
			mCombatDelay += 3.0f;
		else
			mCombatDelay += weapon->Speed();
	}
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

void Player::CombatUpdate()
{
	Hitpoints(mSkills.Level(Skills::SkillIndex::hitpoints));
	RemainingHitpoints(mSkills.EffectiveLevel(Skills::SkillIndex::hitpoints));

	CombatEntity::Update();
}

void Player::CalculateBonuses()
{
	mStatBonus.Reset();

	for (int i = 0; i < Gear::GEAR_SIZE; i++)
	{
		if (Equipment* equipment = dynamic_cast<Equipment*>(mGear.GetItem(i).get()))
		{
			mStatBonus += equipment->Bonuses();
		}
	}
}

void Player::HandleDeath()
{
	mTarget = nullptr;

	mEatDelay = 0.0f;
	mDrinkDelay = 0.0f;

	mInCombat = false;
	mCombatTimer = 0.0f;
	mCombatDelay = 0.0f;

	delete mAction;
	mAction = nullptr;

	mPrayerBook->ToggleAllOff();
	mSkills.Reset();

	ResetPath();
	MapPosition(mSpawn);
}

void Player::Update()
{
	HandleDelays();

	mSkills.Update();

	HandlePrayer();

	HandleMovement();

	CombatUpdate();

	if (mAction)
	{
		mAction->Update();
		if (mAction->Complete())
		{
			delete mAction;
			mAction = nullptr;
		}
	}

	if (Dead()) NotifyObservers();

	Square::Graphics::Instance().Camera(Pos());
}

void Player::Render()
{
	mSprite->Render();
	RenderHealthBar();
}