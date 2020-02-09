#pragma once

#include "Game/Items/Equipment.h"
#include "Game/Definitions/WeaponDefinition.h"
#include "Game/Definitions/RangedDefinition.h"

class Weapon : public Equipment
{
private:
	WeaponDefinition* mWeaponDefinition;
	RangedDefinition* mRangedDefinition;

protected:
	Weapon(int index, int amount = 1)
		: Equipment(index, amount)
	{
		mWeaponDefinition = nullptr;
		mRangedDefinition = nullptr;
	}

	friend class ItemFactory;

public:
	virtual ~Weapon() = default;

	inline bool TwoHanded() const { return mWeaponDefinition->TwoHanded(); }
	inline float Speed() const { return mWeaponDefinition->Speed(); }
	inline int Reach() const { return mWeaponDefinition->Reach(); }

	inline bool IsRanged() const { return mRangedDefinition != nullptr; }
	inline int Type() const { return (IsRanged() ? mRangedDefinition->Type() : -1); }
	std::vector<int> AmmoIndex() const { return (IsRanged() ? mRangedDefinition->AmmoIndex() : std::vector<int>()); }
};