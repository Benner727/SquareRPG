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

bool ShopInventory::CanAdd(std::shared_ptr<Item> item) const
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

void ShopInventory::Add(std::shared_ptr<Item> item)
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

std::shared_ptr<Item> ShopInventory::GetItem(int slot) const
{
	if (slot > -1 && slot < Size())
		return mItems[slot];

	return nullptr;
}

void ShopInventory::Clear()
{
	mItems.clear();
}

void ShopInventory::Reset()
{
	Clear();
	SetStock(mStock);
}
