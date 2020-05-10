#pragma once

#include <Game/GridObject.h>
#include "Game/Map/Map.h"
#include "Game/Items/Item.h"
#include "Npc/Npc.h"

class GameGrid
{
private:
	Map mMap;

public:
	GameGrid(Map& map);
	~GameGrid();

	std::vector<GridObject*> GetGridObjects(Point p);
};