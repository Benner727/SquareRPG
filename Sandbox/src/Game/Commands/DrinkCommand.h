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

		if (Potion* potion = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot)))
			return !mPlayer->HasDrinkDelay();

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();
		Potion* potion = dynamic_cast<Potion*>(mPlayer->Inventory().GetItem(activeSlot));

		mPlayer->SetDrinkDelay();

		for (auto skillBoost : potion->SkillBoost())
			mPlayer->Skills().BoostSkill(skillBoost.SkillIndex(), skillBoost.Add(), skillBoost.Modifier(), potion->RestoreOnly());

		if (potion->ReplaceIndex() != -1)
			mPlayer->Inventory().Replace(activeSlot, ItemFactory::Instance().GetItem(potion->ReplaceIndex()));
		else
			mPlayer->Inventory().Remove(activeSlot);

		mPlayer->Inventory().ActiveSlot(-1);
	}
};