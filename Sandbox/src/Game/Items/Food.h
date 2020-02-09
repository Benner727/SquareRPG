#pragma once

#include "Game/Items/Item.h"
#include "Game/Definitions/FoodDefinition.h"

class Food : public Item
{
private:
	FoodDefinition* mFoodDefinition;

protected:
	Food(int index, int amount = 1) 
		: Item(index, amount) 
	{ 
		mFoodDefinition = nullptr; 
	}

	friend class ItemFactory;

public:
	virtual ~Food() = default;

	inline int ReplaceIndex() const { return mFoodDefinition->ReplaceIndex(); }
	inline int HealAmount() const { return mFoodDefinition->HealAmount(); }
};