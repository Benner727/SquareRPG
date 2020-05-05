#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Map/Pathfinder.h"

#include <list>

class MoveCommand : public ICommand
{
private:
	Player* mPlayer;
	Map* mMap;
	std::list<Point> mPath;

public:
	MoveCommand(Player* player, Map* map)
	{
		mPlayer = player;
		mMap = map;
	}

	~MoveCommand() = default;

	bool CanExecute()
	{
		mPath.clear();

		if (mMap && mPlayer->Target())
		{
			Point target;
			target.x = mPlayer->Target()->Pos().x / 32.0f;
			target.y = mPlayer->Target()->Pos().y / 32.0f;
			target.z = mPlayer->MapPosition().z;

			static PathFinder pathFinder(*mMap);
			mPath = pathFinder.GeneratePath(mPlayer->MapPosition(), target);
		}

		return (mPath.size() > 0);
	}

	void Execute()
	{
		mPlayer->PathTo(mPath);
		mPlayer->Target(nullptr);
	}
};