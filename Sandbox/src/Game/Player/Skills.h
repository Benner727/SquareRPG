#pragma once

#include <Square.h>

#include <algorithm>

#include "Skill.h"

class Skills
{
public:
	enum SkillIndex { hitpoints, attack, strength, defense,
		ranged, prayer, magic, TOTAL_SKILLS};

private:
	std::vector<std::shared_ptr<Skill>> mSkills;
	int mCombatLevel;

	void CalculateCombatLevel();

public:
	Skills();
	~Skills() = default;

	inline int Experience(int index) const { return mSkills[index]->Experience(); }
	inline int EffectiveLevel(int index) const { return mSkills[index]->EffectiveLevel(); }
	inline int Level(int index) const { return mSkills[index]->Level(); }

	inline int CombatLevel() const { return mCombatLevel; }

	void AddExperience(int skill, int amount);

	void Heal(int amount);
	void TakeDamage(int amount);
	void DrainSkill(int skill, int amount);
	void BoostSkill(int skill, int add, int modifier, bool restoreOnly);
	void RestoreSkill(int skill);

	std::vector<std::shared_ptr<Skill>> GetSkills() { return mSkills; }

	void Update();
};