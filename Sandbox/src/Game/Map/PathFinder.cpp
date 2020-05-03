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

	for (int direction = 0; direction < Direction::TOTAL_DIRECTIONS; direction++)
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

std::list<Point> PathFinder::GeneratePath(Point source, Point destination)
{
	mStart = source;
	mEnd = destination;
	std::list<Point> path;

	mOpenNodes.clear();
	mClosedNodes.clear();
	
	Node n;
	n.cost = 0;
	n.distance = 0;
	n.position = mStart;
	n.parent = 0;

	mOpenNodes.push_back(n);

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
