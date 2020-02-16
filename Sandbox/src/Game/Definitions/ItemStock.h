#pragma once

class ItemStock
{
private:
	int mIndex;
	int mAmount;

public:
	ItemStock(int index, int amount)
	{
		mIndex = index;
		mAmount = amount;
	}

	~ItemStock() = default;

	inline int Index() const { return mIndex; }
	inline int Amount() const { return mAmount; }
};