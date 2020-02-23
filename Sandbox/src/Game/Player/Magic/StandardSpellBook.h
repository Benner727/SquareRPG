#pragma once

#include "Game/Player/Magic/ISpellBook.h"
#include "Game/Items/ItemFactory.h"

class StandardSpellBook : public ISpellBook
{
public:
	StandardSpellBook()
	{
		auto& itemFactory = ItemFactory::Instance();

		mSpells.push_back(Spell(1, "Wind Bolt", 1, {}, 2, 6, "WindBoltIcon.png"));
		mSpells.push_back(Spell(2, "Frost Bolt", 5, {}, 4, 8, "FrostBoltIcon.png"));
		mSpells.push_back(Spell(3, "Earth Bolt", 9, {}, 6, 10, "EarthBoltIcon.png"));
		mSpells.push_back(Spell(4, "Fire Bolt", 13, {}, 8, 12, "FireBoltIcon.png"));
	}

	~StandardSpellBook() = default;
};