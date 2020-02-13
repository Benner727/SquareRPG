#pragma once

#include <Square.h>

#include "Game/Items/ItemRepository.h"
#include "Game/Items/Item.h"
#include "Game/Items/Food.h"
#include "Game/Items/Potion.h"
#include "Equipment.h"
#include "Weapon.h"

class ItemFactory
{
private:
	ItemRepository& mItemRepository;

	ItemFactory();
	~ItemFactory();

public:
	static ItemFactory& Instance();

	Item* GetItem(int index, int amount = 1);
};