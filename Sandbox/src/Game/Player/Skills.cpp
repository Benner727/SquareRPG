#include "Game/Player/Skills.h"

Skills::Skills()
{

}

void Skills::AddExperience(int skill, int amount)
{
}

void Skills::Heal(int amount)
{
	if (mSkills[SkillIndex::hitpoints].EffectiveLevel() < mSkills[SkillIndex::hitpoints].Level())
	{
		mSkills[SkillIndex::hitpoints].EffectiveLevel(mSkills[SkillIndex::hitpoints].EffectiveLevel() + amount);

		if (mSkills[SkillIndex::hitpoints].EffectiveLevel() > mSkills[SkillIndex::hitpoints].Level())
			mSkills[SkillIndex::hitpoints].EffectiveLevel(mSkills[SkillIndex::hitpoints].Level());
	}
}

void Skills::TakeDamage(int amount)
{
	mSkills[SkillIndex::hitpoints].EffectiveLevel(mSkills[SkillIndex::hitpoints].EffectiveLevel() - amount);
	
	if (mSkills[SkillIndex::hitpoints].EffectiveLevel() < 1)
		mSkills[SkillIndex::hitpoints].EffectiveLevel(0);
}

void Skills::DrainSkill(int skill, int amount)
{
	mSkills[skill].EffectiveLevel(mSkills[skill].EffectiveLevel() - amount);

	if (mSkills[skill].EffectiveLevel() < 1)
		mSkills[skill].EffectiveLevel(skill == SkillIndex::prayer ? 0 : 1);
}

void Skills::BoostSkill(int skill, int add, int modifier, bool restoreOnly)
{
	if (mSkills[skill].EffectiveLevel() < mSkills[skill].Level() && restoreOnly)
	{
		mSkills[skill].EffectiveLevel(mSkills[skill].EffectiveLevel() + mSkills[skill].Level() * modifier + add);

		if (mSkills[skill].EffectiveLevel() >= mSkills[skill].Level())
			mSkills[skill].EffectiveLevel(mSkills[skill].Level());
	}
	else if (!restoreOnly)
	{
		mSkills[skill].EffectiveLevel(mSkills[skill].EffectiveLevel() + mSkills[skill].Level() * modifier + add);

		if (mSkills[skill].EffectiveLevel() > (mSkills[skill].Level() + mSkills[skill].Level() * modifier + add) && (modifier || add))
			mSkills[skill].EffectiveLevel(mSkills[skill].Level() + mSkills[skill].Level() * modifier + add);

		if (mSkills[skill].EffectiveLevel() < 0)
			mSkills[skill].EffectiveLevel(0);
	}

	mSkills[skill].UpdateTimer(60.0f);
}

void Skills::RestoreSkill(int skill)
{
	mSkills[skill].EffectiveLevel(mSkills[skill].Level());
}

void Skills::Update()
{
	for (int i = 0; i < SkillIndex::TOTAL_SKILLS; i++)
	{
		if (mSkills[i].EffectiveLevel() != mSkills[i].Level())
		{
			if (mSkills[i].UpdateTimer() <= 0.0f)
			{
				if (mSkills[i].EffectiveLevel() < mSkills[i].Level())
					mSkills[i].EffectiveLevel(mSkills[i].EffectiveLevel() + 1);
				else
					mSkills[i].EffectiveLevel(mSkills[i].EffectiveLevel() - 1);

				mSkills[i].UpdateTimer(60.0f);
			}
			else
				mSkills[i].UpdateTimer(mSkills[i].UpdateTimer() - Square::Timer::Instance().DeltaTime());
		}
	}
}