#pragma once

#include "Game/Map/Tile.h"
#include "Game/Map/GroundItem.h"

class Cell : public Square::GameObject
{
private:
	std::shared_ptr<Tile*> mTile;
	std::vector<std::shared_ptr<GroundItem*>> mGroundItems;

public:
	Cell(std::shared_ptr<Tile*> tile = std::make_shared<Tile*>(), std::vector<Item*> groundItems = {});
	~Cell();

	inline std::shared_ptr<Tile*> GetTile() const { return mTile; }
	inline std::vector<std::shared_ptr<GroundItem*>>& GetGroundItems() { return mGroundItems; }

	void AddGroundItem(Item* item);

	void Update();
	void Render();
};