#pragma once

#include <array>

class StatBonus
{
public:
	enum BonusIndex {
		MeleeAttack, MagicAttack, RangedAttack,
		MeleeDefense, MagicDefense, RangedDefense,
		Strength, Prayer, TOTAL_BONUSES
	};

private:
	std::array<int, BonusIndex::TOTAL_BONUSES> mBonuses;

public:
	StatBonus() 
	{
		Reset();
	}

	StatBonus(std::array<int, BonusIndex::TOTAL_BONUSES> bonuses)
	{
		mBonuses = bonuses;
	}

	~StatBonus() = default;

	inline void Bonus(int index, int bonus) { mBonuses[index] = bonus; }
	inline int Bonus(int index) const { return mBonuses[index]; }

	inline void Reset() 
	{
		for (int i = 0; i < BonusIndex::TOTAL_BONUSES; i++)
			mBonuses[i] = 0;
	}

	inline StatBonus& operator +=(const StatBonus& other)
	{
		for (int i = 0; i < BonusIndex::TOTAL_BONUSES; i++)
			mBonuses[i] += other.mBonuses[i];

		return *this;
	}
};