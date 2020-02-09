#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class DrinkCommand : public ICommand
{
private:
	Player* mPlayer;

public:
	DrinkCommand(Player* player)
	{
		mPlayer = player;
	}

	~DrinkCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Potion* food = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot)))
			return !mPlayer->HasDrinkDelay();

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();
		Potion* potion = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot));

		mPlayer->SetDrinkDelay();

		// Add code to boost stats here

		if (potion->ReplaceIndex() != -1)
			mPlayer->Inventory().Replace(activeSlot, ItemFactory::Instance().GetItem(potion->ReplaceIndex()));
		else
			mPlayer->Inventory().Remove(activeSlot);

		mPlayer->Inventory().ActiveSlot(-1);
	}
};