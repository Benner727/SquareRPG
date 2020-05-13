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

	mIcons.push_back(new Square::Sprite("Graphics/head.png"));
	mIcons.push_back(new Square::Sprite("Graphics/cape.png"));
	mIcons.push_back(new Square::Sprite("Graphics/neck.png"));
	mIcons.push_back(new Square::Sprite("Graphics/weapon.png"));
	mIcons.push_back(new Square::Sprite("Graphics/chest.png"));
	mIcons.push_back(new Square::Sprite("Graphics/shield.png"));
	mIcons.push_back(new Square::Sprite("Graphics/legs.png"));
	mIcons.push_back(new Square::Sprite("Graphics/gloves.png"));
	mIcons.push_back(new Square::Sprite("Graphics/boots.png"));
	mIcons.push_back(new Square::Sprite("Graphics/ring.png"));
	mIcons.push_back(new Square::Sprite("Graphics/ammo.png"));

	for (int i = 0; i < mIcons.size(); i++)
	{
		mIcons[i]->Parent(this);
		mIcons[i]->Pos(mSlotPos[i]);
	}
}

int GearInterface::PosToSlot(Square::Vector2 pos)
{
	for (int slot = 0; slot < mSlotPos.size(); slot++)
	{
		Square::Vector2 slotStartPos = mSlotPos[slot];
		Square::Vector2 slotEndPos = slotStartPos + SLOT_SIZE;

		bool WithinSlot = (
			this->Pos().x + slotStartPos.x - SLOT_SIZE / 2 <= pos.x &&
			this->Pos().y + slotStartPos.y - SLOT_SIZE / 2 <= pos.y &&
			this->Pos().x + slotEndPos.x - SLOT_SIZE / 2 > pos.x &&
			this->Pos().y + slotEndPos.y - SLOT_SIZE / 2 > pos.y
		);

		if (WithinSlot)
			return slot;
	}
	return -1;
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
