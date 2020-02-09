#pragma once

#include <vector>

class ItemRepositort;

class RangedDefinition
{
private:
	int mIndex;
	int mType; // 0 = Shot, 1 = thrown
	std::vector<int> mAmmoIndex;

	RangedDefinition(int index, int type, std::vector<int> ammoIndex)
	{
		mIndex = index;
		mType = type;
		mAmmoIndex = ammoIndex;
	}

	~RangedDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline int Type() const { return mType; }
	std::vector<int> AmmoIndex() const { return mAmmoIndex; }
};