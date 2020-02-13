#pragma once

#include <vector>

#include "SkillBoost.h"

class PotionDefinition
{
private:
	int mIndex;
	int mReplaceIndex;
	bool mRestoreOnly;
	std::vector<SkillBoost> mSkillBoost;

	PotionDefinition(int index, int replaceIndex, bool restoreOnly,
		std::vector<SkillBoost> skillBoost)
	{
		mIndex = index;
		mReplaceIndex = replaceIndex;
		mRestoreOnly = restoreOnly;
		mSkillBoost = skillBoost;
	}

	~PotionDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline int ReplaceIndex() const { return mReplaceIndex; }
	inline bool RestoreOnly() const { return mRestoreOnly; }
	inline std::vector<SkillBoost> SkillBoost() const { return mSkillBoost; }
};