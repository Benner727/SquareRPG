#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Gear.h"

class GearInterface : public IMenuTab
{
private:
	Gear& mGear;

	std::string GetAction();

	void CreateActionMenu();

	inline void SetActiveSlot(int slot) { mGear.ActiveSlot(slot); }
	inline bool IsActiveSlot(int slot) { return slot == mGear.ActiveSlot(); }
	inline void Swap(int slotOne, int slotTwo) {}
	Square::GameObject* GetSlot(int slot, bool includeActive = true);

public:
	GearInterface(Gear& gear);
	~GearInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos, bool includeActive = true);
};