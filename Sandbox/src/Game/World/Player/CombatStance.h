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

	CombatOption mActiveOption;

public:
	CombatStance()
	{
		mMeleeOption = CombatOption::melee_accurate;
		mRangedOption = CombatOption::ranged_accurate;
		mMagicOption = CombatOption::melee_accurate;

		mCombatStyle = CombatStyle::melee;

		mActiveOption = CombatOption::melee_accurate;
	}

	~CombatStance() = default;

	void NewOption(CombatOption activeOption) { mActiveOption = activeOption; }
	CombatOption NewOption() const { return mActiveOption; }

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
		switch (mCombatStyle)
		{
		case CombatStyle::melee:
			mMeleeOption = option;
			break;
		case CombatStyle::ranged:
			mRangedOption = option;
			break;
		case CombatStyle::magic:
			mMagicOption = option;
			break;
		default:
			mMeleeOption = option;
		}
	}

	inline void UpdateCombatStyle(CombatStyle style) { mCombatStyle = style; }
	inline CombatStyle GetCombatStyle() const { return mCombatStyle; }
};