#include "Skills.h"

static const int EXP_FOR_LEVEL[] = { 0, 83, 174, 276, 388, 512, 650, 801, 969, 1154, 1358,
1584, 1833, 2107, 2411, 2746, 3115, 3523, 3973, 4470, 5018, 5624, 6291, 7028, 7842,
8740, 9730, 10824, 12031, 13363, 14833, 16456, 18247, 20224, 22406, 24815, 27473, 30408,
33648, 37224, 41171, 45529, 50339, 55649, 61512, 67983, 75127, 83014, 91721, 101333,
111945, 123660, 136594, 150872, 166636, 184040, 203254, 224466, 247886, 273742, 302288,
333804, 368599, 407015, 449428, 496254, 547953, 605032, 668051, 737627, 814445, 899257,
992895, 1096278, 1210421, 1336443, 1475581, 1629200, 1798808, 1986068, 2192818, 2421087,
2673114, 2951373, 3258594, 3597792, 3972294, 4385776, 4842295, 5346332, 5902831,
6517253, 7195629, 7944614, 8771558, 9684577, 10692629, 11805606, 13034431, 14391160 };

Skills::Skills()
{
	mCombatLevel = 1;

	mSkills.push_back(std::make_shared<Skill>("Hitpoints", 1154, 10, 10));
	mSkills.push_back(std::make_shared<Skill>("Attack"));
	mSkills.push_back(std::make_shared<Skill>("Strength"));
	mSkills.push_back(std::make_shared<Skill>("Defense"));
	mSkills.push_back(std::make_shared<Skill>("Ranged"));
	mSkills.push_back(std::make_shared<Skill>("Prayer"));
	mSkills.push_back(std::make_shared<Skill>("Magic"));

	if (mSkills.size() != SkillIndex::TOTAL_SKILLS)
		LOG(ERROR) << "Skills size do nat match.";

	CalculateCombatLevel();
}

void Skills::CalculateCombatLevel()
{
	float base = (mSkills[SkillIndex::defense]->Level() + mSkills[SkillIndex::hitpoints]->Level() + floor(mSkills[SkillIndex::prayer]->Level() * 0.5f)) * 0.25f;

	float melee = (mSkills[SkillIndex::attack]->Level() + mSkills[SkillIndex::strength]->Level()) * 0.325f;
	float range = floor(mSkills[SkillIndex::ranged]->Level() * 1.5f) * 0.325f;
	float mage = floor(mSkills[SkillIndex::magic]->Level() * 1.5f) * 0.325f;

	mCombatLevel = floor(base + std::max(melee, std::max(range, mage)));
}

void Skills::AddExperience(int skill, int amount)
{
	int experience = mSkills[skill]->Experience() + amount;
	int effectiveLevel = mSkills[skill]->EffectiveLevel();
	int level = mSkills[skill]->Level();

	for (int i = level; i < 100; i++)
	{
		if (experience >= EXP_FOR_LEVEL[i])
		{
			effectiveLevel++;
			level++;
		}
	}

	mSkills[skill]->Experience(experience);

	if (mSkills[skill]->Level() != level)
	{
		if (SkillIndex::prayer != skill || mSkills[skill]->EffectiveLevel() > 0)
			mSkills[skill]->EffectiveLevel(effectiveLevel);
		mSkills[skill]->Level(level);

		mSkills[skill]->UpdateLevelText();
		CalculateCombatLevel();
	}
}

void Skills::Heal(int amount)
{
	if (mSkills[SkillIndex::hitpoints]->EffectiveLevel() < mSkills[SkillIndex::hitpoints]->Level())
	{
		mSkills[SkillIndex::hitpoints]->EffectiveLevel(mSkills[SkillIndex::hitpoints]->EffectiveLevel() + amount);

		if (mSkills[SkillIndex::hitpoints]->EffectiveLevel() > mSkills[SkillIndex::hitpoints]->Level())
			mSkills[SkillIndex::hitpoints]->EffectiveLevel(mSkills[SkillIndex::hitpoints]->Level());

		mSkills[SkillIndex::hitpoints]->UpdateLevelText();
	}
}

void Skills::TakeDamage(int amount)
{
	mSkills[SkillIndex::hitpoints]->EffectiveLevel(mSkills[SkillIndex::hitpoints]->EffectiveLevel() - amount);
	
	if (mSkills[SkillIndex::hitpoints]->EffectiveLevel() < 1)
		mSkills[SkillIndex::hitpoints]->EffectiveLevel(0);

	mSkills[SkillIndex::hitpoints]->UpdateLevelText();
}

void Skills::DrainSkill(int skill, int amount)
{
	mSkills[skill]->EffectiveLevel(mSkills[skill]->EffectiveLevel() - amount);

	if (mSkills[skill]->EffectiveLevel() < 1)
		mSkills[skill]->EffectiveLevel(skill == SkillIndex::prayer ? 0 : 1);

	mSkills[skill]->UpdateLevelText();
	mSkills[skill]->UpdateTimer(60.0f);
}

void Skills::BoostSkill(int skill, int add, int modifier, bool restoreOnly)
{
	if (mSkills[skill]->EffectiveLevel() < mSkills[skill]->Level() && restoreOnly)
	{
		mSkills[skill]->EffectiveLevel(mSkills[skill]->EffectiveLevel() + mSkills[skill]->Level() * modifier + add);

		if (mSkills[skill]->EffectiveLevel() >= mSkills[skill]->Level())
			mSkills[skill]->EffectiveLevel(mSkills[skill]->Level());
	}
	else if (!restoreOnly)
	{
		mSkills[skill]->EffectiveLevel(mSkills[skill]->EffectiveLevel() + mSkills[skill]->Level() * modifier + add);

		if (mSkills[skill]->EffectiveLevel() > (mSkills[skill]->Level() + mSkills[skill]->Level() * modifier + add) && (modifier || add))
			mSkills[skill]->EffectiveLevel(mSkills[skill]->Level() + mSkills[skill]->Level() * modifier + add);

		if (mSkills[skill]->EffectiveLevel() < 0)
			mSkills[skill]->EffectiveLevel(0);
	}

	mSkills[skill]->UpdateLevelText();
	mSkills[skill]->UpdateTimer(60.0f);
}

void Skills::RestoreSkill(int skill)
{
	mSkills[skill]->EffectiveLevel(mSkills[skill]->Level());
	mSkills[skill]->UpdateTimer(60.0f);
}

void Skills::Update()
{
	for (int i = 0; i < SkillIndex::TOTAL_SKILLS; i++)
	{
		if (mSkills[i]->EffectiveLevel() != mSkills[i]->Level() && i != SkillIndex::prayer)
		{
			if (mSkills[i]->UpdateTimer() <= 0.0f)
			{
				if (mSkills[i]->EffectiveLevel() < mSkills[i]->Level())
					mSkills[i]->EffectiveLevel(mSkills[i]->EffectiveLevel() + 1);
				else
					mSkills[i]->EffectiveLevel(mSkills[i]->EffectiveLevel() - 1);

				mSkills[i]->UpdateLevelText();
				mSkills[i]->UpdateTimer(60.0f);
			}
			else
				mSkills[i]->UpdateTimer(mSkills[i]->UpdateTimer() - Square::Timer::Instance().DeltaTime());
		}
	}
}