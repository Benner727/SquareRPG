#pragma once

#include "Game/Map/Tile.h"
#include "Game/Map/GroundItem.h"

class Cell : public Square::GameObject
{
private:
	Tile* mTile;
	std::vector<GroundItem*> mGroundItems;

public:
	Cell(Tile* tile = nullptr, std::vector<GroundItem*> groundItems = {});
	~Cell();

	inline Tile* GetTile() const { return mTile; }
	inline std::vector<GroundItem*>& GetGroundItems() { return mGroundItems; }

	void AddGroundItem(Item* item);

	void Update();
	void Render();
};