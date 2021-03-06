#pragma once

#include "Game/Interface/Tabs/IMenuTab.h"
#include "Game/World/Player/Inventory.h"

class InventoryInterface : public IMenuTab
{
private:
	Inventory& mInventory;

	std::string GetAction();

	void CreateActionMenu();

	inline void SetActiveSlot(int slot) { mInventory.ActiveSlot(slot); }
	inline bool IsActiveSlot(int slot) { return slot == mInventory.ActiveSlot(); }
	inline void Swap(int slotOne, int slotTwo) { mInventory.Swap(slotOne, slotTwo); }
	std::shared_ptr<Square::GameObject> GetSlot(int slot, bool includeActive = true);

public:
	InventoryInterface(Inventory& inventory);
	~InventoryInterface() = default;

	std::shared_ptr<Square::GameObject> GetSlot(Square::Vector2 pos, bool includeActive = true);
};