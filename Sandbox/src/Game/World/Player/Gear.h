#pragma once

#include "Game/World/Player/IItemContainer.h"
#include "Game/Items/Weapon.h"

class Gear : public IItemContainer
{
public:
	enum EquipmentSlot { head, cape, neck, weapon, chest, shield, 
		legs, gloves, boots, ring, ammo, TOTAL_SLOTS};

	static const int GEAR_SIZE = EquipmentSlot::TOTAL_SLOTS;

private:
	std::shared_ptr<Item> mItems[GEAR_SIZE];

public:
	Gear();
	~Gear();

	bool CanAdd(std::shared_ptr<Item> item) const;
	void Add(std::shared_ptr<Item> item);

	void Remove(int slot, int amount = 1);
	void Replace(int slot, std::shared_ptr<Item> item);

	void SetNull(int slot);

	std::shared_ptr<Item> GetItem(int slot) const;

	bool HasItem(int index, int amount = 1) const;
	bool HasItems(std::vector<std::shared_ptr<Item>> items) const;

	void RemoveItem(int index, int amount = 1);

	void Clear();
};