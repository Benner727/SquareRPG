#pragma once

#include <Game/GridObject.h>
#include "Game/Map/Map.h"
#include "Game/Items/Item.h"
#include "Npc/Npc.h"

class GameGrid
{
private:
	std::shared_ptr<Map> mMap;

public:
	GameGrid(std::shared_ptr<Map> map);
	~GameGrid();

	std::vector<GridObject*> GetGridObjects(Point p);
};