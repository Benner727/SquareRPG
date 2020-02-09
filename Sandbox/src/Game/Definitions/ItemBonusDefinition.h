#pragma once

#include <array>

class ItemBonusDefinition
{
public:
	enum ItemBonus { 
		MeleeAttack, MagicAttack, RangeAttack, 
		MeleeDefense, MagicDefense, RangeDefense, 
		Strength, Prayer, TOTAL_BONUSES };

private:
	int mIndex;
	std::array<int,TOTAL_BONUSES> mBonuses;

	ItemBonusDefinition(int index, std::array<int, TOTAL_BONUSES> bonuses)
	{
		mIndex = index;
		mBonuses = bonuses;
	}

	~ItemBonusDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline std::array<int, TOTAL_BONUSES> Bonuses() const { return mBonuses; }
};