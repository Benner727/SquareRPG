#include "GearInterface.h"

GearInterface::GearInterface(Gear& gear)
	: IMenuTab("Graphics/panel_gear.png", 32, false, false), mGear(gear)
{
	InitializeGearPositions();
}

void GearInterface::InitializeGearPositions()
{
	mGearPositions = {
	{ Gear::EquipmentSlot::head, {COL_THREE_X, ROW_ONE_Y} },
	{ Gear::EquipmentSlot::cape, {COL_TWO_X, ROW_TWO_Y} },
	{ Gear::EquipmentSlot::neck, {COL_THREE_X, ROW_TWO_Y} },
	{ Gear::EquipmentSlot::weapon, {COL_ONE_X, ROW_THREE_Y} },
	{ Gear::EquipmentSlot::chest, {COL_THREE_X, ROW_THREE_Y} },
	{ Gear::EquipmentSlot::shield, {COL_FIVE_X, ROW_THREE_Y} },
	{ Gear::EquipmentSlot::legs, {COL_THREE_X, ROW_FOUR_Y} },
	{ Gear::EquipmentSlot::gloves, {COL_ONE_X, ROW_FIVE_Y} },
	{ Gear::EquipmentSlot::boots, {COL_THREE_X, ROW_FIVE_Y} },
	{ Gear::EquipmentSlot::ring, {COL_FIVE_X, ROW_FIVE_Y} },
	{ Gear::EquipmentSlot::ammo, {COL_FOUR_X, ROW_TWO_Y} },
	};

	mGearDefaultSprites = {
	{ Gear::EquipmentSlot::head, Square::Sprite("Graphics/head.png") },
	{ Gear::EquipmentSlot::cape, Square::Sprite("Graphics/cape.png") },
	{ Gear::EquipmentSlot::neck, Square::Sprite("Graphics/neck.png") },
	{ Gear::EquipmentSlot::weapon, Square::Sprite("Graphics/weapon.png") },
	{ Gear::EquipmentSlot::chest, Square::Sprite("Graphics/chest.png") },
	{ Gear::EquipmentSlot::shield, Square::Sprite("Graphics/shield.png") },
	{ Gear::EquipmentSlot::legs, Square::Sprite("Graphics/legs.png") },
	{ Gear::EquipmentSlot::gloves, Square::Sprite("Graphics/gloves.png") },
	{ Gear::EquipmentSlot::boots, Square::Sprite("Graphics/boots.png") },
	{ Gear::EquipmentSlot::ring, Square::Sprite("Graphics/ring.png") },
	{ Gear::EquipmentSlot::ammo, Square::Sprite("Graphics/ammo.png") },
	};
}

void GearInterface::CustomRender()
{
	for (int slot = 0; slot < Gear::EquipmentSlot::TOTAL_SLOTS; slot++)
	{
		if (Item* item = mGear.GetItem(slot))
		{
			item->Parent(this);
			item->Pos(mGearPositions[(Gear::EquipmentSlot)slot]);
			item->Render(true);
		}
		else
		{
			Square::Sprite defaultSprite = mGearDefaultSprites[(Gear::EquipmentSlot)slot];
			defaultSprite.Parent(this);
			defaultSprite.Pos(mGearPositions[(Gear::EquipmentSlot)slot]);
			defaultSprite.Render(true);
		}
	}
}

int GearInterface::PosToSlot(Square::Vector2 pos)
{
	for (auto const& gear : mGearPositions)
	{
		Square::Vector2 gearStartPos = gear.second;
		Square::Vector2 gearEndPos = gearStartPos + SLOT_SIZE;

		bool WithinSlot = (
			this->Pos().x + gearStartPos.x - SLOT_SIZE / 2 <= pos.x &&
			this->Pos().y + gearStartPos.y - SLOT_SIZE / 2 <= pos.y &&
			this->Pos().x + gearEndPos.x - SLOT_SIZE / 2 > pos.x&&
			this->Pos().y + gearEndPos.y - SLOT_SIZE / 2 > pos.y
			);
		if (WithinSlot)
		{
			return gear.first;
		}
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
