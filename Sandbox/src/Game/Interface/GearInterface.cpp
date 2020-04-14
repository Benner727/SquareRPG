#include "GearInterface.h"

GearInterface::GearInterface(Gear& gear)
	: IMenuTab("Graphics/panel_brown.png", 32, false, false), mGear(gear)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			mSlotPos.push_back(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
		}
	}
}

std::string GearInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Item* item = dynamic_cast<Item*>(GetSlot(pos)))
	{
		action = "Unequip";
	}

	return action;
}

void GearInterface::CreateActionMenu()
{
	if (Item* item = dynamic_cast<Item*>(GetSlot(Square::InputHandler::Instance().MousePos())))
	{
		mActionsMenu = new ActionsMenu(item->Name(), { "Unequip" }, Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
	}
}

Square::GameObject* GearInterface::GetSlot(int slot, bool includeActive)
{
	Item* item = nullptr;

	if (slot != -1)
	{
		if (includeActive || (slot != mGear.ActiveSlot() && !includeActive))
			item = mGear.GetItem(slot);
	}

	return item;
}

Square::GameObject* GearInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}