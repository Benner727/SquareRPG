#pragma once

#include <list>
#include <algorithm>

#include "Game/Point.h"
#include "Game/Map/Map.h"

class PathFinder
{
private:
	struct Node
	{
		Point position;
		Point parent;
		int distance;
		int cost;

		bool operator == (const Point& other)
		{
			return position == other;
		}

		Node()
		{
		}
	};

	const int ORTHOGONAL_COST = 10;
	const int DIAGONAL_COST = 14;
	const int MAX_COST = 448; // 32 tiles

	const Map& mMap;
	Point mStart;
	Point mEnd;
	std::list<Node> mOpenNodes;
	std::list<Node> mClosedNodes;

	bool mUseDiagonals;

	bool CanWalkTo(Point p, int direction);
	bool FillOpenNodes(Node& n);
	bool UnviablePoint(Point p, int cost);
	int CalculateDistanceToEnd(Point p);

public:
	PathFinder(const Map& map);
	~PathFinder();
	
	std::list<Point> GeneratePath(Point source, Point destination, bool useDiagonals = true);

	static bool InAttackRange(const Map& map, Point p1, Point p2, int range);
};