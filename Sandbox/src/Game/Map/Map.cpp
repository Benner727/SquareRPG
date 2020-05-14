#include "Map.h"

Map::Map()
{
	std::map<int, std::vector<Cell*>> cells;
	
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			cells[0].push_back(new Cell(std::make_shared<Tile*>(new Tile(true, false, new Square::Sprite("Tile.png"), nullptr, {"Walk Here"}))));
		}
	}

	cells[0].at(3 + 5 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));
	cells[0].at(3 + 6 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));
	cells[0].at(3 + 7 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));
	cells[0].at(3 + 8 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));
	cells[0].at(4 + 5 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));
	cells[0].at(5 + 5 * 256) = new Cell(std::make_shared<Tile*>(new Tile(false, false, new Square::Sprite("Wall.png"), nullptr, {})));

	mRegions.push_back(new Region(0, 0, cells));

	Square::Graphics::Instance().SetLimit(Square::VEC2_ONE * mRegions.size() * Region::SIZE * 32.0f);
}

Map::~Map()
{
	for (auto region : mRegions)
		delete region;
}

Cell* Map::GetCell(Point p) const
{
	Cell* cell = nullptr;

	for (auto region : mRegions)
	{
		if (region->Contains(p))
		{
			cell = region->Cells(p.z)[p.x + p.y * Region::SIZE];
			break;
		}
	}

	return cell;
}

std::vector<std::string> Map::TileCommands(Point p)
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = *cell->GetTile();
		return (tile) ? tile->Commands() : std::vector<std::string>();
	}

	return std::vector<std::string>();
}

bool Map::TileWalkable(Point p) const
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = *cell->GetTile();
		return (tile) ? tile->Walkable() : false;
	}

	return false;
}

bool Map::TileCanAttackOver(Point p) const
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = *cell->GetTile();
		return (tile) ? tile->CanAttackOver() : false;
	}

	return false;
}

void Map::Update(int z)
{
	for (auto region : mRegions)
	{
		for (auto cells : region->Cells(z))
		{
			cells->Update();
		}
	}
}

void Map::Render(int z)
{
	for (auto region : mRegions)
	{
		for (auto cells : region->Cells(z))
		{
			cells->Render();
		}
	}
}
