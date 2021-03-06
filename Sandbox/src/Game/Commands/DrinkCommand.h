#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class DrinkCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	DrinkCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~DrinkCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Potion* potion = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return !mPlayer->HasDrinkDelay();

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();
		
		if (Potion* potion = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot).get()))
		{
			mPlayer->SetDrinkDelay();

			for (auto skillBoost : potion->SkillBoost())
				mPlayer->Skills().BoostSkill(skillBoost.SkillIndex(), skillBoost.Add(), skillBoost.Modifier(), potion->RestoreOnly());

			if (potion->ReplaceIndex() != -1)
				mPlayer->Inventory().Replace(activeSlot, ItemFactory::Instance().GetItem(potion->ReplaceIndex()));
			else
				mPlayer->Inventory().Remove(activeSlot);
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};