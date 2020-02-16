#pragma once

#include <string>
#include <vector>

#include "ItemStock.h"

class NpcShopDefinition
{
private:
	int mIndex;
	std::string mName;
	bool mBuysAll;
	std::vector<ItemStock> mStock;

	NpcShopDefinition(int index, std::string name, bool buysAll, std::vector<ItemStock> stock)
	{
		mIndex = index;
		mName = name;
		mBuysAll = buysAll;
		mStock = stock;
	}

	~NpcShopDefinition() = default;

	friend class NpcRepository;

public:
	inline int Index() const { return mIndex; }
	inline std::string Name() const { return mName; }
	inline bool BuysAll() const { return mBuysAll; }
	inline std::vector<ItemStock> Stock() const { return mStock; }
};