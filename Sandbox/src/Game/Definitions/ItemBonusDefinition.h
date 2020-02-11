#pragma once

#include "Game/Player/StatBonus.h"

class ItemBonusDefinition
{
private:
	int mIndex;
	StatBonus mBonuses;

	ItemBonusDefinition(int index, std::array<int, StatBonus::BonusIndex::TOTAL_BONUSES> bonuses)
		: mBonuses(bonuses)
	{
		mIndex = index;
	}

	~ItemBonusDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline StatBonus Bonuses() const { return mBonuses; }
};