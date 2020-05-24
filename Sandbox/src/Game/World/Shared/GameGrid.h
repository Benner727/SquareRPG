#pragma once

#include <Game/World/Shared/GridObject.h>
#include "Game/World/Map/Map.h"
#include "Game/Items/Item.h"
#include "Game/World/Npc/NpcHandler.h"

class GameGrid
{
private:
	std::shared_ptr<Map> mMap;
	NpcHandler& mNpcHandler;

public:
	GameGrid(std::shared_ptr<Map> map, NpcHandler& npcHandler);
	~GameGrid();

	std::vector<std::shared_ptr<GridObject>> GetGridObjects(Square::Vector2 pos, int z);
};