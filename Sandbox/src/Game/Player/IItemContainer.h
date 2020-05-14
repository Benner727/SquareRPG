#pragma once

#include <vector>

#include "Game/Items/Item.h"

class IItemContainer
{
protected:
	int mActiveSlot;

public:
	virtual void ActiveSlot(int slot) { mActiveSlot = slot; }
	virtual int ActiveSlot() const { return mActiveSlot; }

	virtual bool CanAdd(std::shared_ptr<Item> item) const = 0;
	virtual void Add(std::shared_ptr<Item> item) = 0;

	virtual void Remove(int slot, int amount = 1) = 0;
	virtual void SetNull(int slot) = 0;

	virtual std::shared_ptr<Item> GetItem(int slot) const = 0;

	virtual void Clear() = 0;
};