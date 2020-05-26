#include "GameGrid.h"

GameGrid::GameGrid(std::shared_ptr<Map> map, std::shared_ptr<NpcHandler> npcHandler)
	: mMap(map), mNpcHandler(npcHandler)
{
}

GameGrid::~GameGrid()
{
}

std::vector<std::shared_ptr<GridObject>> GameGrid::GetGridObjects(Square::Vector2 pos, int z)
{
	Point p(pos, z);
	std::vector<std::shared_ptr<GridObject>> mGridObjects;

	for (const auto& npc : mNpcHandler->GetPos(pos, z))
	{
		for (const auto& action : npc->Actions())
		{
			std::string command = action + " -> " + npc->Name();
			if (NpcFighter* npcFighter = dynamic_cast<NpcFighter*>(npc.get()))
				command += " (Lvl " + std::to_string(npcFighter->Level()) + ")";

			mGridObjects.push_back(std::make_shared<GridObject>(command, npc));
		}
	}

	Cell* cell = mMap->GetCell(p);
	if (cell)
	{
		for (const auto& groundItem : cell->GetGroundItems())
		{
			for (const auto& action : groundItem->Actions())
			{
				mGridObjects.push_back(std::make_shared<GridObject>(action, groundItem));
			}
		}

		for (const auto& command : cell->GetTile()->Commands())
			mGridObjects.push_back(std::make_shared<GridObject>(command, cell->GetTile()));
	}

	return mGridObjects;
}