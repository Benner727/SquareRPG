#include "PathFinder.h"

bool PathFinder::CanWalkTo(Point p, int direction)
{
	switch (direction)
	{
	case Direction::north:
		return mMap.TileWalkable(p + Point(0, -1));
		break;
	case Direction::east:
		return mMap.TileWalkable(p + Point(1, 0));
		break;
	case Direction::south:
		return mMap.TileWalkable(p + Point(0, 1));
		break;
	case Direction::west:
		return mMap.TileWalkable(p + Point(-1, 0));
		break;
	case Direction::northeast:
		return mMap.TileWalkable(p + Point(0, -1)) && mMap.TileWalkable(p + Point(1, 0)) && mMap.TileWalkable(p + Point(1, -1));
		break;
	case Direction::northwest:
		return mMap.TileWalkable(p + Point(0, -1)) && mMap.TileWalkable(p + Point(-1, 0)) && mMap.TileWalkable(p + Point(-1, -1));
		break;
	case Direction::southeast:
		return mMap.TileWalkable(p + Point(0, 1)) && mMap.TileWalkable(p + Point(1, 0)) && mMap.TileWalkable(p + Point(1, 1));
		break;
	case Direction::southwest:
		return mMap.TileWalkable(p + Point(0, 1)) && mMap.TileWalkable(p + Point(-1, 0)) && mMap.TileWalkable(p + Point(-1, 1));
		break;
	}
}

bool PathFinder::FillOpenNodes(Node& n)
{
	int stepCost, distanceFromStart, distanceFromEnd;
	Point neighbor;
	Node newNode;

	int total_directions = 4;
	if (mUseDiagonals) total_directions = 8;

	for (int direction = 0; direction < total_directions; direction++)
	{
		if (CanWalkTo(n.position, direction))
		{
			neighbor = n.position;
			neighbor.Translate(direction);
			if (neighbor == mEnd) return true;
			
			stepCost = (direction < 4) ? ORTHOGONAL_COST : DIAGONAL_COST;
			distanceFromStart = n.cost + stepCost;
			distanceFromEnd = CalculateDistanceToEnd(neighbor);

			newNode.position = neighbor;
			newNode.parent = n.position;
			newNode.distance = distanceFromEnd;
			newNode.cost = distanceFromStart;
			if (distanceFromStart < MAX_COST && !UnviablePoint(neighbor, distanceFromStart + distanceFromEnd))
				mOpenNodes.push_back(newNode);
		}
	}
	return false;
}

bool PathFinder::UnviablePoint(Point p, int cost)
{
	std::list<Node>::iterator i = std::find(mClosedNodes.begin(), mClosedNodes.end(), p);
	if (i != mClosedNodes.end())
	{
		if ((*i).cost + (*i).distance < cost) return true;
		mClosedNodes.erase(i);
		return false;
	}

	i = std::find(mOpenNodes.begin(), mOpenNodes.end(), p);
	if (i != mOpenNodes.end())
	{
		if ((*i).cost + (*i).distance < cost) return true;
		mOpenNodes.erase(i);
		return false;
	}

	return false;
}

int PathFinder::CalculateDistanceToEnd(Point p)
{
	int x = abs(mEnd.x - p.x);
	int y = abs(mEnd.y - p.y);
	const int D = 10;
	const int D2 = 14;
	return D * (x + y) + (D2 - 2*D) * std::min(x, y);
}

PathFinder::PathFinder(const Map& map)
	: mMap(map)
{
}

PathFinder::~PathFinder()
{
}

std::list<Point> PathFinder::GeneratePath(Point source, Point destination, bool useDiagonals)
{
	mStart = source;
	mEnd = destination;
	mUseDiagonals = useDiagonals;
	std::list<Point> path;

	mOpenNodes.clear();
	mClosedNodes.clear();
	
	Node n;
	n.cost = 0;
	n.distance = 0;
	n.position = mStart;
	n.parent = 0;

	mOpenNodes.push_back(n);

	if (source == destination)
		return path;

	while (!mOpenNodes.empty())
	{
		mClosedNodes.push_back(mOpenNodes.front());
		mOpenNodes.pop_front();

		if (FillOpenNodes(mClosedNodes.back()))
		{
			path.push_front(mEnd);
			path.push_front(mClosedNodes.back().position);

			Point parentPosition = mClosedNodes.back().parent;
			for (std::list<Node>::reverse_iterator i = mClosedNodes.rbegin(); i != mClosedNodes.rend(); i++)
			{
				if ((*i).position == parentPosition && !((*i).position == mStart))
				{
					path.push_front((*i).position);
					parentPosition = (*i).parent;
				}
			}

			path.push_front(mStart);
			break;
		}
	}

	return path;
}

bool PathFinder::InAttackRange(const Map& map, Point p1, Point p2, int range)
{
	if (p1 == p2)
		return false;

	if (range == 1)
	{
		for (int direction = 0; direction < 4; direction++)
		{
			Point p = p2;
			p.Translate(direction);
			if (p1 == p)
				return true;
		}

		return false;
	}

	std::vector<Point> points;

	int dx = p2.x - p1.x;
	// if x1 == x2, then it does not matter what we set here
	int ix((dx > 0) - (dx < 0));

	dx = abs(dx) << 1;

	int dy = p2.y - p1.y;
	// if y1 == y2, then it does not matter what we set here
	int iy((dy > 0) - (dy < 0));
	dy = abs(dy) << 1;

	if (dx >= dy)
	{
		// error may go below zero
		int error(dy - (dx >> 1));

		while (p1.x != p2.x)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= dx;
				p1.y += iy;
			}
			// else do nothing

			error += dy;
			p1.x += ix;

			if (map.TileCanAttackOver(p1)) points.push_back(p1);
			else return false;
		}
	}
	else
	{
		// error may go below zero
		int error(dx - (dy >> 1));

		while (p1.y != p2.y)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= dy;
				p1.x += ix;
			}
			// else do nothing

			error += dx;
			p1.y += iy;

			if (map.TileCanAttackOver(p1)) points.push_back(p1);
			else return false;
		}
	}

	return points.size() <= range;
}
