#pragma once

#include <Square.h>

enum Direction {
	north,
	east,
	south,
	west,
	northeast,
	northwest,
	southeast,
	southwest,
	TOTAL_DIRECTIONS
};

struct Point
{
	int x, y, z;
	
	Point(int _x = 0, int _y = 0, int _z = 0)
		: x(_x), y(_y), z(_z)
	{
	}

	Point(Square::Vector2 pos, int _z = 0)
	{
		x = pos.x / 32.0f;
		y = pos.y / 32.0f;
		z = _z;
	}

	Square::Vector2 ToVector2()
	{
		Square::Vector2 vec;
		vec.x = x * 32.0f + 16.0f;
		vec.y = y * 32.0f + 16.0f;

		return vec;
	}

	void Translate(int dir)
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

	bool operator < (const Point& rhs) const
	{
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	bool operator == (const Point& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator != (const Point& other)
	{
		return x != other.x || y != other.y || z != other.z;
	}

	Point operator + (const Point& other)
	{
		return Point(x + other.x, y + other.y, z + other.z);
	}
};