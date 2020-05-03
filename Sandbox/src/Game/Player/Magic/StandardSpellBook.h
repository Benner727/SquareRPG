#pragma once

#include "Game/Player/Magic/ISpellBook.h"
#include "Game/Items/ItemFactory.h"

class StandardSpellBook : public ISpellBook
{
public:
	StandardSpellBook()
	{
		auto& itemFactory = ItemFactory::Instance();

		mSpells.push_back(new Spell(1, "Wind Bolt", 1, { itemFactory.GetItem(6, 1), itemFactory.GetItem(7, 1) }, 2, 6, "MagicIcons/WindBoltIcon.png"));
		mSpells.push_back(new Spell(2, "Frost Bolt", 5, {}, 4, 8, "MagicIcons/FrostBoltIcon.png"));
		mSpells.push_back(new Spell(3, "Earth Bolt", 9, {}, 6, 10, "MagicIcons/EarthBoltIcon.png"));
		mSpells.push_back(new Spell(4, "Fire Bolt", 13, {}, 8, 12, "MagicIcons/FireBoltIcon.png"));
	}

	virtual ~StandardSpellBook() = default;
};