#pragma once

#include <Square.h>

class Skills
{
public:
	enum SkillIndex { hitpoints, attack, strength, defense,
		ranged, prayer, magic, TOTAL_SKILLS};

private:
	class Skill
	{
	private:
		int mExperience;
		int mEffectiveLevel;
		int mLevel;
		float mUpdateTimer;

	public:
		Skill(int experience = 0, int effectiveLevel = 1, int level = 1)
		{
			mExperience = experience;
			mEffectiveLevel = effectiveLevel;
			mLevel = level;
			mUpdateTimer = 0.0f;
		}

		~Skill() = default;

		inline int Experience() const { return mExperience; }
		inline int EffectiveLevel() const { return mEffectiveLevel; }
		inline int Level() const { return mLevel; }
		inline float UpdateTimer() const { return mUpdateTimer; }

		inline void Experience(int experience) { mExperience = experience; }
		inline void EffectiveLevel(int effectiveLevel) { mEffectiveLevel = effectiveLevel; }
		inline void Level(int level) { mLevel = level; }
		inline void UpdateTimer(float updateTimer) { mUpdateTimer = updateTimer; }
	};

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