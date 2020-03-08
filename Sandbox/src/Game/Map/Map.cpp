#include "Map.h"

Map::Map()
{
	std::map<int, std::vector<Tile*>> tiles;
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			tiles[0].push_back(new Tile(true, false, new Square::Sprite("Tile.png"), nullptr, {}));
		}
	}

	mRegions.push_back(new Region(0, 0, tiles));
}

Map::~Map()
{
}

Tile* Map::GetTile(Point p)
{
	Tile* tile = nullptr;

	for (auto region : mRegions)
	{
		if (region->Contains(p))
		{
			tile = region->Tiles(p.z)[(p.x - Region::SIZE) + (p.y - Region::SIZE) * Region::SIZE];
			break;
		}
	}

	return tile;
}

std::vector<std::string> Map::TileCommands(Point p)
{
	Tile* tile = GetTile(p);
	return (tile) ? tile->Commands() : std::vector<std::string>();
}

bool Map::TileWalkable(Point p)
{
	Tile* tile = GetTile(p);
	return (tile) ? tile->Walkable() : false;
}

bool Map::TileCanAttackOver(Point p)
{
	Tile* tile = GetTile(p);
	return (tile) ? tile->CanAttackOver() : false;
}

void Map::Update(int z)
{
	for (auto region : mRegions)
	{
		for (auto tiles : region->Tiles(z))
		{
			tiles->Update();
		}
	}
}

void Map::Render(int z)
{
	for (auto region : mRegions)
	{
		for (auto tiles : region->Tiles(z))
		{
			tiles->Render();
		}
	}
}
