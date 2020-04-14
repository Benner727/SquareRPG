#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Inventory.h"

class InventoryInterface : public IMenuTab
{
private:
	Inventory& mInventory;

	std::string GetAction();

	void CreateActionMenu();

	inline void SetActiveSlot(int slot) { mInventory.ActiveSlot(slot); }
	inline bool IsActiveSlot(int slot) { return slot == mInventory.ActiveSlot(); }
	inline void Swap(int slotOne, int slotTwo) { mInventory.Swap(slotOne, slotTwo); }
	Square::GameObject* GetSlot(int slot, bool includeActive = true);

public:
	InventoryInterface(Inventory& inventory);
	~InventoryInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos, bool includeActive = true);
};