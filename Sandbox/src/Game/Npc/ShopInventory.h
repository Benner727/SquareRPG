#pragma once

#include "Game/Player/IItemContainer.h"
#include "Game/Definitions/ItemStock.h"
#include "Game/Items/ItemFactory.h"

class ShopInventory : public IItemContainer
{
private:
	static const int MAX_SHOP_SIZE = 20;

	std::vector<std::shared_ptr<Item>> mItems;
	std::vector<ItemStock> mStock;

public:
	ShopInventory();
	~ShopInventory();

	void SetStock(std::vector<ItemStock> stock);

	bool CanAdd(std::shared_ptr<Item> item) const;
	void Add(std::shared_ptr<Item> item);

	void Remove(int slot, int amount = 1);
	void SetNull(int slot);

	std::shared_ptr<Item> GetItem(int slot) const;

	void Clear();
	void Reset();

	inline int Size() const { return mItems.size(); }
};