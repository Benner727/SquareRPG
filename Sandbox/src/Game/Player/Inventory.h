#pragma once

#include "Game/Player/IItemContainer.h"

class Inventory : public IItemContainer
{
public:
	static const int INVENTORY_SIZE = 20;

private:
	Item* mItems[INVENTORY_SIZE];

public:
	Inventory();
	~Inventory();

	bool CanAdd(Item* item) const;
	void Add(Item* item);

	void Remove(int slot, int amount = 1);
	void Replace(int slot, Item* item);
	void Swap(int firstSlot, int secondSlot);

	void SetNull(int slot);

	Item* GetItem(int slot) const;

	bool HasItem(int index, int amount = 1) const;
	bool HasItems(std::vector<Item*> items) const;

	void RemoveItem(int index, int amount = 1);
	void RemoveItems(std::vector<Item*> items);

	void Clear();
};