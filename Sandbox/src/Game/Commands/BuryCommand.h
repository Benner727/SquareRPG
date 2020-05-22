#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"

class BuryCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

	bool CanBury(int itemIndex)
	{
		switch (itemIndex)
		{
		case 10: //bones
			return true;
			break;
		default:
			return false;
		}
	}

	int PrayerExperience(int itemIndex)
	{
		int experience = 0;

		switch (itemIndex)
		{
		case 10: //bones
			experience = 15;
			break;
		default:
			experience = 0;
		}

		return experience;
	}

public:
	BuryCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~BuryCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* item = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return CanBury(item->Index());

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* item = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
		{
			mPlayer->Skills().AddExperience(Skills::SkillIndex::prayer, PrayerExperience(item->Index()));
			mPlayer->Inventory().Remove(activeSlot);
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};