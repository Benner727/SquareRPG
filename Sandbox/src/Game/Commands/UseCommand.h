#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class UseCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	UseCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~UseCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* selected = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return (mPlayer->Target() != nullptr);

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		// To do
		// We might separate use types and execute different commands
		// This will just be the generic use command that calls the others

		if (Item* target = dynamic_cast<Item*>(mPlayer->Target().get()))
		{
			if (Item* selected = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			{
				std::cout << selected->Name() << " -> " << target->Name() << std::endl;
			}
		}

		mPlayer->Inventory().ActiveSlot(-1);
		mPlayer->Target(nullptr);
	}
};