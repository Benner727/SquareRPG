#pragma once

#include "Game/Items/Item.h"
#include "Game/Definitions/EquipmentDefinition.h"
#include "Game/Definitions/ItemBonusDefinition.h"

class Equipment : public Item
{
private:
	EquipmentDefinition* mEquipmentDefinition;
	ItemBonusDefinition* mItemBonusDefinition;

protected:
	Equipment(int index, int amount = 1)
		: Item(index, amount)
	{
		mEquipmentDefinition = nullptr;
		mItemBonusDefinition = nullptr;
	}

	friend class ItemFactory;

public:
	virtual ~Equipment() = default;

	inline int Index() const { return mEquipmentDefinition->Index(); }
	inline int Slot() const { return mEquipmentDefinition->Slot(); }
	inline std::vector<SkillRequirement> Requirements() { return mEquipmentDefinition->Requirements(); }
	inline std::array<int, ItemBonusDefinition::ItemBonus::TOTAL_BONUSES> Bonuses() const { return mItemBonusDefinition->Bonuses(); }
};