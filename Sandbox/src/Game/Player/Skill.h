#pragma once

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