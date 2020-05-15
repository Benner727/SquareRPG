#include "GearInterface.h"

GearInterface::GearInterface(Gear& gear)
	: IMenuTab("Graphics/panel_gear.png", 32, false, false), mGear(gear)
{
	InitializeGearPositions();
}

void GearInterface::InitializeGearPositions()
{
	mSlotPos.resize(Gear::EquipmentSlot::TOTAL_SLOTS);
	mSlotPos[Gear::EquipmentSlot::head] = { COL_THREE_X, ROW_ONE_Y };
	mSlotPos[Gear::EquipmentSlot::cape] = { COL_TWO_X, ROW_TWO_Y };
	mSlotPos[Gear::EquipmentSlot::neck] = { COL_THREE_X, ROW_TWO_Y };
	mSlotPos[Gear::EquipmentSlot::weapon] = { COL_ONE_X, ROW_THREE_Y };
	mSlotPos[Gear::EquipmentSlot::chest] = { COL_THREE_X, ROW_THREE_Y };
	mSlotPos[Gear::EquipmentSlot::shield] = { COL_FIVE_X, ROW_THREE_Y };
	mSlotPos[Gear::EquipmentSlot::legs] = { COL_THREE_X, ROW_FOUR_Y };
	mSlotPos[Gear::EquipmentSlot::gloves] = { COL_ONE_X, ROW_FIVE_Y };
	mSlotPos[Gear::EquipmentSlot::boots] = { COL_THREE_X, ROW_FIVE_Y };
	mSlotPos[Gear::EquipmentSlot::ring] = { COL_FIVE_X, ROW_FIVE_Y };
	mSlotPos[Gear::EquipmentSlot::ammo] = { COL_FOUR_X, ROW_TWO_Y };

	mIcons.push_back(new Square::Sprite("GearIcons/head.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/cape.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/neck.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/weapon.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/chest.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/shield.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/legs.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/gloves.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/boots.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/ring.png"));
	mIcons.push_back(new Square::Sprite("GearIcons/ammo.png"));

	for (int i = 0; i < mIcons.size(); i++)
	{
		mIcons[i]->Parent(this);
		mIcons[i]->Pos(mSlotPos[i]);
	}
}

std::string GearInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Item* item = dynamic_cast<Item*>(GetSlot(pos).get()))
	{
		action = "Unequip";
	}

	return action;
}

void GearInterface::CreateActionMenu()
{
	if (Item* item = dynamic_cast<Item*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		mActionsMenu = new ActionsMenu(item->Name(), { "Unequip" }, Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
	}
}

std::shared_ptr<Square::GameObject> GearInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<Item> item = nullptr;

	if (slot != -1)
	{
		if (includeActive || (slot != mGear.ActiveSlot() && !includeActive))
			item = mGear.GetItem(slot);
	}

	return item;
}

std::shared_ptr<Square::GameObject> GearInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);
	return GetSlot(slot, includeActive);
}
