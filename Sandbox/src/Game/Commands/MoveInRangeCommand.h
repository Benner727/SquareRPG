#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Map/Pathfinder.h"

#include <list>

class MoveInRangeCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;
	std::list<Point> mPath;

public:
	MoveInRangeCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	{
		mPlayer = player;
		mMap = map;
	}

	~MoveInRangeCommand() = default;

	bool CanExecute()
	{
		mPath.clear();

		if (mMap && mPlayer->Target())
		{
			Point target;
			target.x = mPlayer->Target()->Pos().x / 32.0f;
			target.y = mPlayer->Target()->Pos().y / 32.0f;
			target.z = mPlayer->MapPosition().z;

			if (mPlayer->MapPosition() != target)
			{
				static PathFinder pathFinder(*mMap);
				mPath = pathFinder.GeneratePath(mPlayer->MapPosition(), target, false);
			}
			else
			{
				static Point direction[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
				for (int i = 0; i < 4; i++)
				{
					if (mMap->TileWalkable(target + direction[i]))
					{
						mPath.push_back(target + direction[i]);
						mPath.push_back(target);
						break;
					}
				}
			}
		}

		return (mPath.size() > 0);
	}

	void Execute()
	{
		int range = 1;
		if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::weapon).get()))
			range = weapon->Reach();

		Point target;
		target.x = mPlayer->Target()->Pos().x / 32.0f;
		target.y = mPlayer->Target()->Pos().y / 32.0f;
		target.z = mPlayer->MapPosition().z;

		for (int i = 0; i < range && mPath.size() > 1; i++)
		{
			Point point = mPath.back();
			mPath.pop_back();
			
			if (!PathFinder::InAttackRange(*mMap, mPath.back(), target, range))
			{
				mPath.push_back(point);
				break;
			}
		}

		mPlayer->PathTo(mPath);
	}
};