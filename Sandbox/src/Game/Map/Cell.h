#pragma once

#include "Game/Map/Tile.h"
#include "Game/Map/GroundItem.h"

class Cell : public Square::GameObject
{
private:
	Tile* mTile;
	std::vector<std::shared_ptr<GroundItem*>> mGroundItems;

public:
	Cell(Tile* tile = nullptr, std::vector<Item*> groundItems = {});
	~Cell();

	inline Tile* GetTile() const { return mTile; }
	inline std::vector<std::shared_ptr<GroundItem*>>& GetGroundItems() { return mGroundItems; }

	void AddGroundItem(Item* item);

	void Update();
	void Render();
};