#pragma once

class SkillRequirement
{
private:
	int mSkillIndex;
	int mLevel;

public:
	SkillRequirement(int skillIndex, int level)
	{
		mSkillIndex = skillIndex;
		mLevel = level;
	}

	~SkillRequirement() = default;

	inline int SkillIndex() const { return mSkillIndex; }
	inline int Level() const { return mLevel; }
};