#pragma once

#include "Game/Map/Tile.h"
#include "Game/Map/GroundItem.h"

class Cell : public Square::GameObject
{
private:
	std::shared_ptr<Tile> mTile;
	std::vector<std::shared_ptr<GroundItem>> mGroundItems;

public:
	Cell(std::shared_ptr<Tile> tile = nullptr, std::vector<std::shared_ptr<Item>> groundItems = {});
	~Cell() = default;

	inline std::shared_ptr<Tile> GetTile() const { return mTile; }
	inline std::vector<std::shared_ptr<GroundItem>>& GetGroundItems() { return mGroundItems; }

	void AddGroundItem(std::shared_ptr<Item> item);

	void Update();
	void Render();
};