#include "Game/Npc/ShopInventory.h"

ShopInventory::ShopInventory()
{

}

ShopInventory::~ShopInventory()
{
	Clear();
}

void ShopInventory::SetStock(std::vector<ItemStock> stock)
{
	mStock = stock;

	for (auto item : stock)
	{
		mItems.push_back(ItemFactory::Instance().GetItem(item.Index(), item.Amount()));
	}
}

bool ShopInventory::CanAdd(Item* item) const
{
	if (Size() < MAX_SHOP_SIZE)
		return true;

	for (int i = 0; i < Size(); i++)
	{
		if (mItems[i]->Index() == item->Index())
			return true;
	}

	return false;
}

void ShopInventory::Add(Item* item)
{
	if (CanAdd(item))
	{
		for (int i = 0; i < Size(); i++)
		{
			if (mItems[i]->Index() == item->Index())
			{
				mItems[i]->Add(item->Amount());
				return;
			}
		}
		
		mItems.push_back(item);
	}
}

void ShopInventory::Remove(int slot, int amount)
{
	if (slot > -1 && slot < Size())
	{
		mItems[slot]->Remove(amount);

		if (mItems[slot]->Amount() < 1)
		{
			if (slot >= mStock.size() || mStock[slot].Index() != mItems[slot]->Index())
			{
				delete mItems[slot];
				mItems.erase(mItems.begin() + slot);
			}
		}
	}
}

void ShopInventory::SetNull(int slot)
{
	if (slot > -1 && slot < Size())
	{
		mItems.erase(mItems.begin() + slot);
	}
}

Item* ShopInventory::GetItem(int slot) const
{
	if (slot > -1 && slot < Size())
		return mItems[slot];

	return nullptr;
}

void ShopInventory::Clear()
{
	for (auto item : mItems)
		delete item;
	mItems.clear();
}

void ShopInventory::Reset()
{
	Clear();
	SetStock(mStock);
}
