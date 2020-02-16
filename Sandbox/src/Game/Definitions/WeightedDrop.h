#pragma once

class WeightedDrop
{
private:
	int mItemIndex;
	int mWeight;
	int mMinAmount;
	int mMaxAmount;

public:
	WeightedDrop(int itemIndex, int weight, int minAmount, int maxAmount)
	{
		mItemIndex = itemIndex;
		mWeight = weight;
		mMinAmount = minAmount;
		mMaxAmount = maxAmount;
	}

	~WeightedDrop() = default;

	inline int ItemIndex() const { return mItemIndex; }
	inline int Weight() const { return mWeight; }
	inline int MinAmount() const { return mMinAmount; }
	inline int MaxAmount() const { return mMaxAmount; }
};