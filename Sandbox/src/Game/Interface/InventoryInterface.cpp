#include "InventoryInterface.h"

InventoryInterface::InventoryInterface(Inventory& inventory)
	: IMenuTab("Graphics/panel_brown.png", 32, true, false), mInventory(inventory)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mSlotPos.push_back(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
		}
	}
}


std::string InventoryInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Item* item = dynamic_cast<Item*>(GetSlot(pos)))
	{
		action = item->InventoryActions().front();
	}

	return action;
}

void InventoryInterface::CreateActionMenu()
{
	if (Item* item = dynamic_cast<Item*>(GetSlot(Square::InputHandler::Instance().MousePos())))
	{
		mActionsMenu = new ActionsMenu(item->Name(), item->InventoryActions(), Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
	}
}

Square::GameObject* InventoryInterface::GetSlot(int slot, bool includeActive)
{
	Item* item = nullptr;

	if (slot != -1)
	{
		if (includeActive || (slot != mInventory.ActiveSlot() && !includeActive))
			item = mInventory.GetItem(slot).get();
	}

	return item;
}

Square::GameObject* InventoryInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}