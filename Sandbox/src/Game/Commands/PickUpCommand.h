#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Map/Map.h"

class PickUpCommand : public ICommand
{
private:
	Player* mPlayer;
	Map* mMap;

public:
	PickUpCommand(Player* player, Map* map)
	{
		mPlayer = player;
		mMap = map;
	}

	~PickUpCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (GroundItem* groundItem = dynamic_cast<GroundItem*>(mPlayer->Target()))
		{
			if (mPlayer->MapPosition() == Point(groundItem->Pos()))
				return mPlayer->Inventory().CanAdd(groundItem->GetItem());
		}

		return false;
	}

	void Execute()
	{
		GroundItem* groundItem = dynamic_cast<GroundItem*>(mPlayer->Target());

		mPlayer->Inventory().Add(groundItem->GetItem());
		groundItem->RemoveItem();
	}
};