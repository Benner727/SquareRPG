#pragma once

#include "Game/World/Player/Magic/ISpellBook.h"
#include "Game/Items/ItemFactory.h"

class StandardSpellBook : public ISpellBook
{
public:
	StandardSpellBook()
	{
		auto& itemFactory = ItemFactory::Instance();

		std::vector<std::shared_ptr<Item>> itemReq = {};
		mSpells.push_back(std::make_shared<Spell>(1, "Wind Bolt", 1, itemReq, 2, 6, true, "MagicIcons/WindBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(2, "Frost Bolt", 5, itemReq, 4, 12, false, "MagicIcons/FrostBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(3, "Earth Bolt", 9, itemReq, 6, 18, true, "MagicIcons/EarthBoltIcon.png"));
		mSpells.push_back(std::make_shared<Spell>(4, "Fire Bolt", 13, itemReq, 8, 24, true, "MagicIcons/FireBoltIcon.png"));

		InitCombatSpells();
	}

	virtual ~StandardSpellBook() = default;
};