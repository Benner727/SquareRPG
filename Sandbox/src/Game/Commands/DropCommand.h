#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"

class DropCommand : public ICommand
{
private:
	Player* mPlayer;

public:
	DropCommand(Player* player)
	{
		mPlayer = player;
	}

	~DropCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* selected = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot)))
			return true;

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		Item* item = mPlayer->Inventory().GetItem(activeSlot);
		mPlayer->Inventory().SetNull(activeSlot);
		
		// To do - Place item on ground

		mPlayer->Inventory().ActiveSlot(-1);
	}
};