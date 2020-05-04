#pragma once

#include <Square.h>

#include "Game/Definitions/ItemDefinition.h"

class Item : public Square::GameObject
{
private:
	int mIndex;
	int mAmount;

	Square::Sprite* mSprite;

	ItemDefinition* mItemDefinition;

protected:
	Item(int index, int amount = 1);

	friend class ItemFactory;

public:
	virtual ~Item();

	inline int Index() const { return mIndex; }
	inline int Amount() const { return mAmount; }

	inline std::string Name() const { return mItemDefinition->Name(); }
	inline bool Stackable() const { return mItemDefinition->Stackable(); }
	inline int AlchemyPrice() const { return mItemDefinition->AlchemyPrice(); }
	inline int GeneralPrice() const { return mItemDefinition->GeneralPrice(); }
	inline std::vector<std::string> InventoryActions() const { return mItemDefinition->InventoryActions(); }
	inline std::vector<std::string> GroundActions() const { return mItemDefinition->GroundActions(); }

	inline void Add(int amount = 1) { mAmount += amount; }
	inline void Remove(int amount = 1) { mAmount -= amount; }

	void Render(bool ignoreCamera = false);
};