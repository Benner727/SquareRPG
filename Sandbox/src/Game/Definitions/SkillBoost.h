#pragma once

class SkillBoost
{
private:
	int mSkillIndex;
	int mAdd;
	double mModifier;

public:
	SkillBoost(int skillIndex, int add, int modifier)
	{
		mSkillIndex = skillIndex;
		mAdd = add;
		mModifier = modifier;
	}

	~SkillBoost() = default;

	inline int SkillIndex() const { return mSkillIndex; }
	inline int Add() const { return mAdd; }
	inline double Modifier() const { return mModifier; }
};