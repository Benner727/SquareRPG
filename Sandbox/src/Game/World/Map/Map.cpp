#include "Map.h"

Map::Map()
{
	/*
	std::map<int, std::vector<Cell*>> cells;

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			std::vector<std::string> actions = { "Walk Here" };
			if (y == 0 || x == 0 || y == 255 || x == 255)
				cells[0].push_back(new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>())));
			else if (y == 20)
				cells[0].push_back(new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>())));
			else
				cells[0].push_back(new Cell(std::make_shared<Tile>(true, true, new Square::Sprite("Tile.png"), nullptr, actions)));
		}
	}

	cells[0].at(3 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(3 + 6 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(3 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(3 + 8 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(4 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(5 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));

	cells[0].at(10 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(10 + 6 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(10 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(11 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(11 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(12 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(12 + 6 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(12 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));

	cells[0].at(15 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 6 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 8 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 9 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 10 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(15 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(16 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 5 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 6 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 7 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 8 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 9 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(17 + 10 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(14 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(13 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(12 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(18 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(19 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));
	cells[0].at(20 + 11 * 256) = new Cell(std::make_shared<Tile>(false, false, new Square::Sprite("Wall.png"), nullptr, std::vector<std::string>()));

	mRegions.push_back(new Region(0, 0, cells));
	*/

	LoadRegions();

	Square::Graphics::Instance().SetLimit(Square::VEC2_ONE * mRegions.size() * Region::SIZE * 32.0f);
}

Map::~Map()
{
	for (auto region : mRegions)
		delete region;
}

void Map::LoadRegions()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Map/");

	std::ifstream infile(fullPath + "map.txt", std::ifstream::in);
	if (!infile) std::cerr << "map.txt could not be opened!" << std::endl;
	else std::cout << "Loading map..." << std::endl;

	std::string line;

	std::map<int, std::vector<Cell*>> cells;
	std::vector<std::string> actions = { "Walk Here" };

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int tileNum;
		char c;

		while (iss >> tileNum >> c)
		{
			int x = (tileNum % (TILESET_WIDTH / TILE_SIZE)) * TILE_SIZE;
			int y = (tileNum / (TILESET_WIDTH / TILE_SIZE)) * TILE_SIZE;

			cells[0].push_back(new Cell(std::make_shared<Tile>(true, true, new Square::Sprite("Map/Tileset.png", x, y, TILE_SIZE, TILE_SIZE), nullptr, actions)));
			cells[0].back()->Scale(Square::Vector2(2.0f, 2.0f));
		}
	}

	mRegions.push_back(new Region(0, 0, cells));
}

Cell* Map::GetCell(Point p) const
{
	Cell* cell = nullptr;

	for (auto region : mRegions)
	{
		if (region->Contains(p))
		{
			if (!region->Cells(p.z).empty())
			{
				cell = region->Cells(p.z)[p.x + p.y * Region::SIZE];
				break;
			}
		}
	}

	return cell;
}

std::vector<std::string> Map::TileCommands(Point p)
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = cell->GetTile().get();
		return (tile) ? tile->Commands() : std::vector<std::string>();
	}

	return std::vector<std::string>();
}

bool Map::TileWalkable(Point p) const
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = cell->GetTile().get();
		return (tile) ? tile->Walkable() : false;
	}

	return false;
}

bool Map::TileCanAttackOver(Point p) const
{
	Cell* cell = GetCell(p);
	if (cell)
	{
		Tile* tile = cell->GetTile().get();
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
			if (cells) cells->Update();
		}
	}
}

void Map::Render(int z)
{
	for (auto region : mRegions)
	{
		for (auto cells : region->Cells(z))
		{
			if (cells) cells->Render();
		}
	}
}
