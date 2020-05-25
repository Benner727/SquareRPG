#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Actions/WalkToPickUpAction.h"
#include "Game/Interface/MessageLog.h"

class PickUpCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<MessageLog> mMessageLog;

public:
	PickUpCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMap = map;
		mMessageLog = messageLog;
	}

	~PickUpCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (GroundItem* groundItem = dynamic_cast<GroundItem*>(mPlayer->Target().get()))
		{
			if (!groundItem->Expired())
			{
				if (mPlayer->MapPosition() == Point(groundItem->Pos()))
				{
					if (mPlayer->Inventory().CanAdd(groundItem->GetItem()))
					{
						return true;
					}
					else
					{
						mMessageLog->AddMessage("How do you plan on holding that?", { 128, 128, 128, 255 });
						return false;
					}
				}
				else
					mPlayer->SetAction(new WalkToPickUpAction(mPlayer, mMap, mMessageLog));
			}
		}

		return false;
	}

	void Execute()
	{
		GroundItem* groundItem = dynamic_cast<GroundItem*>(mPlayer->Target().get());

		mPlayer->Inventory().Add(groundItem->GetItem());
		groundItem->RemoveItem();
	}
};