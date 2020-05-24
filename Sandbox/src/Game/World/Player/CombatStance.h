#pragma once

#include "Game/Definitions/NpcCombatDefinition.h"

enum class CombatOption {
	melee_accurate, melee_aggressive, melee_defensive, melee_controlled,
	ranged_accurate, ranged_rapid, ranged_longrange,
	magic_standard, magic_defensive
};

class CombatStance
{
private:
	CombatOption mMeleeOption;
	CombatOption mRangedOption;
	CombatOption mMagicOption;

	CombatStyle mCombatStyle;

public:
	CombatStance()
	{
		mMeleeOption = CombatOption::melee_accurate;
		mRangedOption = CombatOption::ranged_accurate;
		mMagicOption = CombatOption::magic_standard;

		mCombatStyle = CombatStyle::melee;
	}

	~CombatStance() = default;

	CombatOption Get() const
	{
		switch (mCombatStyle)
		{
		case CombatStyle::melee:
			return mMeleeOption;
			break;
		case CombatStyle::ranged:
			return mRangedOption;
			break;
		case CombatStyle::magic:
			return mMagicOption;
			break;
		default:
			return mMeleeOption;
		}
	}

	void Set(CombatOption option)
	{
		switch (option)
		{
		case CombatOption::melee_accurate:
		case CombatOption::melee_aggressive:
		case CombatOption::melee_defensive:
		case CombatOption::melee_controlled:
			mMeleeOption = option;
			break;
		case CombatOption::ranged_accurate:
		case CombatOption::ranged_rapid:
		case CombatOption::ranged_longrange:
			mRangedOption = option;
			break;
		case CombatOption::magic_standard:
		case CombatOption::magic_defensive:
			mMagicOption = option;
			break;
		}
	}

	inline void UpdateCombatStyle(CombatStyle style) { mCombatStyle = style; }
	inline CombatStyle GetCombatStyle() const { return mCombatStyle; }
};