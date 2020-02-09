#pragma once

#include <vector>

#include "Game/Definitions/SkillRequirement.h"

class EquipmentDefinition
{
private:
	int mIndex;
	int mSlot;
	std::vector<SkillRequirement> mRequirements;

	EquipmentDefinition(int index, int slot, std::vector<SkillRequirement> requirements)
	{
		mIndex = index;
		mSlot = slot;
		mRequirements = requirements;
	}

	~EquipmentDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline int Slot() const { return mSlot; }
	inline std::vector<SkillRequirement> Requirements() { return mRequirements; }
};