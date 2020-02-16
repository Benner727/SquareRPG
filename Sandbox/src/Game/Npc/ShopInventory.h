#pragma once

#include "Game/Player/IItemContainer.h"
#include "Game/Definitions/ItemStock.h"
#include "Game/Items/ItemFactory.h"

class ShopInventory : public IItemContainer
{
private:
	static const int MAX_SHOP_SIZE = 20;

	std::vector<Item*> mItems;
	std::vector<ItemStock> mStock;

public:
	ShopInventory();
	~ShopInventory();

	void SetStock(std::vector<ItemStock> stock);

	bool CanAdd(Item* item) const;
	void Add(Item* item);

	void Remove(int slot, int amount = 1);
	void SetNull(int slot);

	Item* GetItem(int slot) const;

	void Clear();
	void Reset();

	inline int Size() const { return mItems.size(); }
};