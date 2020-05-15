#pragma once

#include "Game/Player/Magic/ISpellBook.h"
#include "Game/Items/ItemFactory.h"

class StandardSpellBook : public ISpellBook
{
public:
	StandardSpellBook()
	{
		auto& itemFactory = ItemFactory::Instance();

		std::vector<std::shared_ptr<Item>> itemReq = { itemFactory.GetItem(6, 1), itemFactory.GetItem(7, 1) };
		mSpells.push_back(std::make_shared<Spell>(1, "Wind Bolt", 1, itemReq, 2, 6, "MagicIcons/WindBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(2, "Frost Bolt", 5, itemReq, 4, 8, "MagicIcons/FrostBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(3, "Earth Bolt", 9, itemReq, 6, 10, "MagicIcons/EarthBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(4, "Fire Bolt", 13, itemReq, 8, 12, "MagicIcons/FireBoltIcon.png"));
	}

	virtual ~StandardSpellBook() = default;
};