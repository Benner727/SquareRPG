#pragma once

#include "Npc/NpcFighter.h"
#include "Items/ItemFactory.h"
#include "Map/GroundItem.h"
#include "Random.h"

namespace NpcDropFormula
{
	inline std::vector<std::shared_ptr<Item>> Generate(std::vector<WeightedDrop> dropTable)
	{
		std::vector<std::shared_ptr<Item>> drop, temp;
		int dropRoll = floor(99.0f * Random::Float());

		for (int i = 0; i < dropTable.size(); i++)
		{
			if (dropTable[i].Weight() == 100)
			{
				int amount = floor((dropTable[i].MaxAmount() - dropTable[i].MinAmount()) * Random::Float()) + dropTable[i].MinAmount();
				drop.push_back(ItemFactory::Instance().GetItem(dropTable[i].ItemIndex(), amount));
			}
			else if (dropTable[i].Weight() > dropRoll)
			{
				int amount = floor((dropTable[i].MaxAmount() - dropTable[i].MinAmount()) * Random::Float()) + dropTable[i].MinAmount();
				temp.push_back(ItemFactory::Instance().GetItem(dropTable[i].ItemIndex(), amount));
			}
		}

		if (temp.size())
			drop.push_back(temp[rand() % temp.size()]);

		return drop;
	}

};