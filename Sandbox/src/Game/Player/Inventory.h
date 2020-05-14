#pragma once

#include "Game/Player/IItemContainer.h"

class Inventory : public IItemContainer
{
public:
	static const int INVENTORY_SIZE = 20;

private:
	std::shared_ptr<Item> mItems[INVENTORY_SIZE];

public:
	Inventory();
	~Inventory();

	bool CanAdd(std::shared_ptr<Item> item) const;
	void Add(std::shared_ptr<Item> item);

	void Remove(int slot, int amount = 1);
	void Replace(int slot, std::shared_ptr<Item> item);
	void Swap(int firstSlot, int secondSlot);

	void SetNull(int slot);

	std::shared_ptr<Item> GetItem(int slot) const;

	bool HasItem(int index, int amount = 1) const;
	bool HasItems(std::vector<std::shared_ptr<Item>> items) const;

	void RemoveItem(int index, int amount = 1);
	void RemoveItems(std::vector<std::shared_ptr<Item>> items);

	void Clear();
};