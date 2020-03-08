#pragma once

enum class Direction {
	north,
	east,
	south,
	west,
	northeast,
	northwest,
	southeast,
	southwest
};

struct Point
{
	int x, y, z;

	void Translate(Direction dir)
	{
		switch (dir)
		{
		case Direction::north:
			y--;
			break;
		case Direction::south:
			y++;
			break;
		case Direction::west:
			x--;
			break;
		case Direction::east:
			x++;
			break;
		case Direction::northeast:
			y--;
			x++;
			break;
		case Direction::northwest:
			y--;
			x--;
			break;
		case Direction::southeast:
			y++;
			x++;
			break;
		case Direction::southwest:
			y++;
			x--;
			break;
		}
	}
};