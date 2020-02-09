#pragma once

class SkillData
{
private:
	int mSkillIndex;
	int mAdd;
	double mModifier;

public:
	SkillData(int skillIndex, int add, int modifier)
	{
		mSkillIndex = skillIndex;
		mAdd = add;
		mModifier = modifier;
	}

	~SkillData() = default;

	inline int SkillIndex() const { return mSkillIndex; }
	inline int Add() const { return mAdd; }
	inline double Modifier() const { return mModifier; }
};