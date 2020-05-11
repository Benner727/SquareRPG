#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Gear.h"

class GearInterface : public IMenuTab
{
private:
	static const int SLOT_SIZE = 40;
	static const int ROW_ONE_Y = 34;
	static const int ROW_TWO_Y = 80;
	static const int ROW_THREE_Y = 127;
	static const int ROW_FOUR_Y = 175;
	static const int ROW_FIVE_Y = 222;

	static const int COL_ONE_X = 36;
	static const int COL_TWO_X = 50;
	static const int COL_THREE_X = 105;
	static const int COL_FOUR_X = 158;
	static const int COL_FIVE_X = 170;

	Gear& mGear;
	std::map<Gear::EquipmentSlot, Square::Vector2> mGearPositions;
	std::map<Gear::EquipmentSlot, Square::Sprite> mGearDefaultSprites;

	std::string GetAction();
	int PosToSlot(Square::Vector2 pos);

	void CreateActionMenu();
	void InitializeGearPositions();

	inline void SetActiveSlot(int slot) { mGear.ActiveSlot(slot); }
	inline bool IsActiveSlot(int slot) { return slot == mGear.ActiveSlot(); }
	inline void Swap(int slotOne, int slotTwo) {}
	Square::GameObject* GetSlot(int slot, bool includeActive = true);

	void CustomRender();

public:
	GearInterface(Gear& gear);
	~GearInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos, bool includeActive = true);
};