#include "Game/Player/Gear.h"

Gear::Gear()
{
	for (int i = 0; i < GEAR_SIZE; i++)
		mItems[i] = nullptr;

	mActiveSlot = -1;
}

Gear::~Gear()
{
	Clear();
}

bool Gear::CanAdd(std::shared_ptr<Item> item) const
{
	if (Equipment* equipment = dynamic_cast<Equipment*>(item.get()))
	{
		return (mItems[equipment->Slot()] == nullptr);
	}

	return false;
}

void Gear::Add(std::shared_ptr<Item> item)
{
	if (CanAdd(item))
	{
		if (std::shared_ptr<Equipment> equipment = std::dynamic_pointer_cast<Equipment>(item))
		{
			mItems[equipment->Slot()] = equipment;
		}
	}
}

void Gear::Remove(int slot, int amount)
{
	if (slot > -1 && slot < GEAR_SIZE)
	{
		mItems[slot]->Remove(amount);

		if (mItems[slot]->Amount() < 1)
		{
			mItems[slot] = nullptr;
		}
	}
}

void Gear::Replace(int slot, std::shared_ptr<Item> item)
{
	if (slot > -1 && slot < GEAR_SIZE)
	{
		mItems[slot] = item;
	}
}

void Gear::SetNull(int slot)
{
	if (slot > -1 && slot < GEAR_SIZE)
		mItems[slot] = nullptr;
}

std::shared_ptr<Item> Gear::GetItem(int slot) const
{
	if (slot > -1 && slot < GEAR_SIZE)
	{
		return mItems[slot];
	}

	return nullptr;
}

bool Gear::HasItem(int index, int amount) const
{
	int total = 0;

	for (int i = 0; i < GEAR_SIZE; i++)
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

bool Gear::HasItems(std::vector<std::shared_ptr<Item>> items) const
{
	for (auto item : items)
	{
		if (!HasItem(item->Index(), item->Amount()))
			return false;
	}

	return true;
}

void Gear::RemoveItem(int index, int amount)
{
	int slot = 0;

	do
	{
		if (slot > GEAR_SIZE)
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

void Gear::Clear()
{
	for (int i = 0; i < GEAR_SIZE; i++)
	{
		mItems[i] = nullptr;
	}
}