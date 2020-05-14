#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class UnequipCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	UnequipCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~UnequipCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Gear().ActiveSlot();

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Gear().GetItem(activeSlot)))
		{
			return mPlayer->Inventory().CanAdd(equipment);
		}

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Gear().ActiveSlot();

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Gear().GetItem(activeSlot)))
		{
			mPlayer->Gear().SetNull(activeSlot);
			mPlayer->Inventory().Add(equipment);
			mPlayer->CalculateBonuses();
		}

		mPlayer->Gear().ActiveSlot(-1);
	}
};