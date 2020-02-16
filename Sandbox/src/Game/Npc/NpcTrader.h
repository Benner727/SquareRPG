#pragma once

#include "Game/Npc/Npc.h"
#include "Game/Npc/ShopInventory.h"

class NpcTrader : public Npc
{
private:
	ShopInventory mShopInventory;

	NpcShopDefinition* mNpcShopDefinition;

	void Init()
	{
		mShopInventory.SetStock(mNpcShopDefinition->Stock());
	}

protected:

	NpcTrader(int index)
		: Npc(index)
	{
		mNpcShopDefinition = nullptr;
	}

	friend class NpcFactory;

public:
	~NpcTrader() = default;

	inline std::string ShopName() const { return mNpcShopDefinition->Name(); }
	inline bool BuysAll() const { return mNpcShopDefinition->BuysAll(); }
	inline std::vector<ItemStock> Stock() const { return  mNpcShopDefinition->Stock(); }

	inline ShopInventory& ShopInventory() { return mShopInventory; }
};