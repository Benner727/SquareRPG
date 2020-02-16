#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class EatCommand : public ICommand
{
private:
	Player* mPlayer;

public:
	EatCommand(Player* player)
	{
		mPlayer = player;
	}

	~EatCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Food* food = dynamic_cast<Food*>(mPlayer->Inventory().GetItem(activeSlot)))
			return !mPlayer->HasEatDelay();

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();
		
		if (Food* food = dynamic_cast<Food*>(mPlayer->Inventory().GetItem(activeSlot)))
		{
			mPlayer->SetEatDelay();
			mPlayer->Skills().Heal(food->HealAmount());

			if (food->ReplaceIndex() != -1)
				mPlayer->Inventory().Replace(activeSlot, ItemFactory::Instance().GetItem(food->ReplaceIndex()));
			else
				mPlayer->Inventory().Remove(activeSlot);
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};