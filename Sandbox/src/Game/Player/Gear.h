#pragma once

#include "Game/Player/IItemContainer.h"
#include "Game/Items/Weapon.h"

class Gear : public IItemContainer
{
public:
	enum EquipmentSlot { head, cape, neck, weapon, chest, shield, 
		legs, gloves, boots, ring, ammo, TOTAL_SLOTS};

	static const int GEAR_SIZE = EquipmentSlot::TOTAL_SLOTS;

private:
	Item* mItems[GEAR_SIZE];

public:
	Gear();
	~Gear();

	bool CanAdd(Item* item) const;
	void Add(Item* item);

	void Remove(int slot, int amount = 1);
	void Replace(int slot, Item* item);

	void SetNull(int slot);

	Item* GetItem(int slot) const;

	bool HasItem(int index, int amount = 1) const;
	bool HasItems(std::vector<Item*> items) const;

	void RemoveItem(int index, int amount = 1);

	void Clear();
};