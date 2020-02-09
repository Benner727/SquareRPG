#include "Game/Player/Inventory.h"

Inventory::Inventory()
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
		mItems[i] = nullptr;

	mActiveSlot = -1;
}

Inventory::~Inventory()
{
	Clear();
}

bool Inventory::CanAdd(Item* item) const
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (mItems[i] == nullptr)
		{
			return true;
		}
		else
		{
			if (mItems[i]->Index() == item->Index())
			{
				if (mItems[i]->Stackable())
					return true;
			}
		}
	}

	return false;
}

void Inventory::Add(Item* item)
{
	if (CanAdd(item))
	{
		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (mItems[i] != nullptr)
			{
				if (mItems[i]->Index() == item->Index())
				{
					if (mItems[i]->Stackable())
					{
						mItems[i]->Add(item->Amount());
						return;
					}
				}
			}
		}

		for (int i = 0; i < INVENTORY_SIZE; i++)
		{
			if (mItems[i] == nullptr)
			{
				mItems[i] = item;
				return;
			}
		}
	}
}

void Inventory::Remove(int slot, int amount)
{
	if (slot > -1 && slot < INVENTORY_SIZE)
	{
		mItems[slot]->Remove(amount);

		if (mItems[slot]->Amount() < 1)
		{
			delete mItems[slot];
			mItems[slot] = nullptr;
		}
	}
}

void Inventory::Replace(int slot, Item* item)
{
	if (slot > -1 && slot < INVENTORY_SIZE)
	{
		delete mItems[slot];
		mItems[slot] = item;
	}
}

void Inventory::Swap(int firstSlot, int secondSlot)
{
	if (firstSlot > -1 && firstSlot < INVENTORY_SIZE)
	{
		if (secondSlot > -1 && secondSlot < INVENTORY_SIZE)
		{
			Item* temp = mItems[firstSlot];
			mItems[firstSlot] = mItems[secondSlot];
			mItems[secondSlot] = temp;
		}
	}
}

Item* Inventory::GetItem(int slot) const
{
	if (slot > -1 && slot < INVENTORY_SIZE)
		return mItems[slot];

	return nullptr;
}

bool Inventory::HasItem(int index, int amount) const
{
	int total = 0;

	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (mItems[i] != nullptr)
		{
			if (mItems[i]->Index() == index)
			{
				total += mItems[i]->Amount();
			}
		}
	}

	return (total >= amount);
}

bool Inventory::HasItems(std::vector<Item*> items) const
{
	for (auto item : items)
	{
		if (!HasItem(item->Index(), item->Amount()))
			return false;
	}

	return true;
}

void Inventory::RemoveItem(int index, int amount)
{
	int slot = 0;

	do
	{
		if (slot > INVENTORY_SIZE)
			break;

		if (mItems[slot] != nullptr)
		{
			if (mItems[slot]->Index() == index)
			{
				Remove(slot, amount);
				amount -= mItems[slot]->Amount();
			}
		}

	} while (amount > 0);
}

void Inventory::Clear()
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		delete mItems[i];
		mItems[i] = nullptr;
	}
}