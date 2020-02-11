#pragma once

#include <Square.h>

#include "Skill.h"

class Skills
{
public:
	enum SkillIndex { hitpoints, attack, strength, defense,
		ranged, prayer, magic, TOTAL_SKILLS};

private:
	Skill mSkills[SkillIndex::TOTAL_SKILLS];

public:
	Skills();
	~Skills() = default;

	inline int Experience(int index) const { return mSkills[index].Experience(); }
	inline int EffectiveLevel(int index) const { return mSkills[index].EffectiveLevel(); }
	inline int Level(int index) const { return mSkills[index].Level(); }

	void AddExperience(int skill, int amount);

	void Heal(int amount);
	void TakeDamage(int amount);
	void DrainSkill(int skill, int amount);
	void BoostSkill(int skill, int add, int modifier, bool restoreOnly);
	void RestoreSkill(int skill);

	void Update();
};