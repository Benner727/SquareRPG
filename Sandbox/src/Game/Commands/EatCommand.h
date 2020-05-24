#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class EatCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	EatCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~EatCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Food* food = dynamic_cast<Food*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return !mPlayer->HasEatDelay();

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();
		
		if (Food* food = dynamic_cast<Food*>(mPlayer->Inventory().GetItem(activeSlot).get()))
		{
			mPlayer->SetEatDelay();
			mPlayer->Heal(food->HealAmount());

			if (food->ReplaceIndex() != -1)
				mPlayer->Inventory().Replace(activeSlot, ItemFactory::Instance().GetItem(food->ReplaceIndex()));
			else
				mPlayer->Inventory().Remove(activeSlot);
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};