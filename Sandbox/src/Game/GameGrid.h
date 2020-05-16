#pragma once

#include <Game/GridObject.h>
#include "Game/Map/Map.h"
#include "Game/Items/Item.h"
#include "Game/NpcHandler.h"

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