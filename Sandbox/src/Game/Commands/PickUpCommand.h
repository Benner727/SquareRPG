#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Actions/WalkToPickUpAction.h"

class PickUpCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

public:
	PickUpCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
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
			if (!groundItem->Expired())
			{
				if (mPlayer->MapPosition() == Point(groundItem->Pos()))
					return mPlayer->Inventory().CanAdd(groundItem->GetItem());
				else
					mPlayer->SetAction(new WalkToPickUpAction(mPlayer, mMap));
			}
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