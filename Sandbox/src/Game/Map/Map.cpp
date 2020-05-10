#include "Map.h"

Map::Map()
{
	std::map<int, std::vector<Tile*>> tiles;
	
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			tiles[0].push_back(new Tile(true, false, new Square::Sprite("Tile.png"), nullptr, {"Walk Here"}));
		}
	}

	tiles[0].at(3 + 5 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});
	tiles[0].at(3 + 6 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});
	tiles[0].at(3 + 7 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});
	tiles[0].at(3 + 8 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});
	tiles[0].at(4 + 5 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});
	tiles[0].at(5 + 5 * 256) = new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {});

	mRegions.push_back(new Region(0, 0, tiles));

	Square::Graphics::Instance().SetLimit(Square::VEC2_ONE * mRegions.size() * Region::SIZE * 32.0f);
}

Map::~Map()
{
	for (auto region : mRegions)
		delete region;
}

Tile* Map::GetTile(Point p) const
{
	Tile* tile = nullptr;

	for (auto region : mRegions)
	{
		if (region->Contains(p))
		{
			tile = region->Tiles(p.z)[p.x + p.y * Region::SIZE];
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

bool Map::TileWalkable(Point p) const
{
	Tile* tile = GetTile(p);
	return (tile) ? tile->Walkable() : false;
}

bool Map::TileCanAttackOver(Point p) const
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
