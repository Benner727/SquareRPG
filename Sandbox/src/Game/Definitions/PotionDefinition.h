#pragma once

#include <vector>

#include "SkillData.h"

class ItemRepository;

class PotionDefinition
{
private:
	int mIndex;
	int mReplaceIndex;
	bool mRestoreOnly;
	std::vector<SkillData> mSkillData;

	PotionDefinition(int index, int replaceIndex, bool restoreOnly,
		std::vector<SkillData> skillData)
	{
		mIndex = index;
		mReplaceIndex = replaceIndex;
		mRestoreOnly = restoreOnly;
		mSkillData = skillData;
	}

	~PotionDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline int ReplaceIndex() const { return mReplaceIndex; }
	inline bool RestoreOnly() const { return mRestoreOnly; }
	inline std::vector<SkillData> SkillData() const { return mSkillData; }
};