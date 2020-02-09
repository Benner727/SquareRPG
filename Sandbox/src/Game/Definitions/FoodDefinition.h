#pragma once

class ItemRepository;

class FoodDefinition
{
private:
	int mIndex;
	int mReplaceIndex;
	int mHealAmount;

	FoodDefinition(int index, int replaceIndex, int healAmount)
	{
		mIndex = index;
		mReplaceIndex = replaceIndex;
		mHealAmount = healAmount;
	}

	~FoodDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline int ReplaceIndex() const { return mReplaceIndex; }
	inline int HealAmount() const { return mHealAmount; }
};