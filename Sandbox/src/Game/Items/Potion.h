#pragma once

#include "Game/Items/Item.h"
#include "Game/Definitions/PotionDefinition.h"

class Potion : public Item
{
private:
	PotionDefinition* mPotionDefinition;

	Potion(int index, int amount = 1) 
		: Item(index, amount) 
	{
		mPotionDefinition = nullptr;
	}

	friend class ItemFactory;

public:
	virtual ~Potion() = default;

	inline int ReplaceIndex() const { return mPotionDefinition->ReplaceIndex(); }
	inline bool RestoreOnly() const { return mPotionDefinition->RestoreOnly(); }
	inline std::vector<SkillBoost> SkillBoost() const { return mPotionDefinition->SkillBoost(); }
};